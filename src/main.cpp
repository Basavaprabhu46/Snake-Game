// -----------------------------------------------------------------------------
// main.cpp — application entry point.
//
// This file hosts a MINIMAL runnable harness (Application) so the UI modules
// owned by Basava Prabhu (InputHandler, Renderer, MenuScreen, GameOverScreen,
// HighScoreScreen, ScoreEntryOverlay) can be demonstrated end-to-end.
//
// NOTE: The full GameEngine / Snake / Food / CollisionDetector / LevelManager /
// Obstacle / ScoreManager modules are owned by the other team members per the
// SAD. The lightweight snake loop below is a SCAFFOLD ONLY and should be
// replaced by `Game.cpp` (owner: Basavaraj) in Sprint-2.
// -----------------------------------------------------------------------------

#include <algorithm>
#include <random>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "InputHandler.h"
#include "Renderer.h"
#include "Types.h"
#include "screens/GameOverScreen.h"
#include "screens/HighScoreScreen.h"
#include "screens/MenuScreen.h"
#include "screens/ScoreEntryOverlay.h"

namespace snake {

namespace {

constexpr float kEasyTickMs = 150.f;
constexpr float kMediumTickMs = 100.f;
constexpr float kHardTickMs = 70.f;
constexpr float kMinTickMs = 40.f;
constexpr int kMaxLevel = 10;

int initialObstacles(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy:
            return 0;
        case Difficulty::Medium:
            return 5;
        case Difficulty::Hard:
            return 10;
    }
    return 0;
}

float startTick(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy:
            return kEasyTickMs;
        case Difficulty::Medium:
            return kMediumTickMs;
        case Difficulty::Hard:
            return kHardTickMs;
    }
    return kEasyTickMs;
}

bool isOpposite(Command a, Command b) {
    return (a == Command::Up && b == Command::Down) ||
           (a == Command::Down && b == Command::Up) ||
           (a == Command::Left && b == Command::Right) ||
           (a == Command::Right && b == Command::Left);
}

} // namespace

class Application {
public:
    Application()
        : window_(sf::VideoMode(Renderer::windowWidth(), Renderer::windowHeight()),
                  "Snake Game - Team 11", sf::Style::Titlebar | sf::Style::Close),
          renderer_(window_),
          menu_(renderer_),
          gameOver_(renderer_),
          highScore_(renderer_),
          scoreEntry_(renderer_),
          rng_(std::random_device{}()) {
        window_.setFramerateLimit(60);
        renderer_.loadFont();  // non-fatal if missing
        state_ = GameState::MainMenu;
    }

    void run() {
        sf::Clock frameClock;
        while (window_.isOpen()) {
            const float dt = frameClock.restart().asSeconds();
            processEvents();
            update(dt);
            render();
        }
    }

private:
    // --- Event / command handling -----------------------------------------
    void processEvents() {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed) {
                handleCommand(input_.translate(event));
            } else if (event.type == sf::Event::TextEntered) {
                if (state_ == GameState::ScoreEntry) {
                    scoreEntry_.handleText(event.text.unicode);
                }
            }
        }
    }

    void handleCommand(Command command) {
        if (command == Command::None) {
            return;
        }

        switch (state_) {
            case GameState::MainMenu:
                menu_.handleCommand(command);
                applyMenuAction();
                break;

            case GameState::Playing:
                if (InputHandler::isDirection(command)) {
                    if (!isOpposite(command, direction_)) {
                        pendingDirection_ = command;
                    }
                } else if (command == Command::Pause) {
                    state_ = GameState::Paused;
                } else if (command == Command::Menu || command == Command::Back) {
                    state_ = GameState::MainMenu;
                    menu_.reset();
                }
                break;

            case GameState::Paused:
                if (command == Command::Pause || command == Command::Confirm) {
                    state_ = GameState::Playing;
                } else if (command == Command::Menu ||
                           command == Command::Back) {
                    state_ = GameState::MainMenu;
                    menu_.reset();
                }
                break;

            case GameState::GameOver:
                gameOver_.handleCommand(command);
                applyGameOverAction();
                break;

            case GameState::HighScoreView:
                highScore_.handleCommand(command);
                if (highScore_.done()) {
                    state_ = GameState::MainMenu;
                    menu_.reset();
                }
                break;

            case GameState::ScoreEntry:
                scoreEntry_.handleCommand(command);
                if (scoreEntry_.submitted()) {
                    finishScoreEntry();
                }
                break;

            default:
                break;
        }
    }

    void applyMenuAction() {
        const MenuAction action = menu_.action();
        if (action == MenuAction::None) {
            return;
        }
        switch (action) {
            case MenuAction::StartEasy:
                resetGame(Difficulty::Easy);
                break;
            case MenuAction::StartMedium:
                resetGame(Difficulty::Medium);
                break;
            case MenuAction::StartHard:
                resetGame(Difficulty::Hard);
                break;
            case MenuAction::ViewHighScores:
                highScore_.reset();
                state_ = GameState::HighScoreView;
                break;
            case MenuAction::Exit:
                window_.close();
                break;
            default:
                break;
        }
        menu_.clearAction();
    }

    void applyGameOverAction() {
        const GameOverAction action = gameOver_.action();
        if (action == GameOverAction::None) {
            return;
        }
        if (action == GameOverAction::Restart) {
            const Difficulty difficulty = data_.difficulty;
            resetGame(difficulty);
        } else if (action == GameOverAction::MainMenu) {
            state_ = GameState::MainMenu;
            menu_.reset();
        }
        gameOver_.clearAction();
    }

    void finishScoreEntry() {
        ScoreEntry entry;
        entry.initials = scoreEntry_.initials();
        entry.score = data_.score;
        leaderboard_.push_back(entry);
        std::sort(leaderboard_.begin(), leaderboard_.end(),
                  [](const ScoreEntry& a, const ScoreEntry& b) {
                      return a.score > b.score;
                  });
        if (leaderboard_.size() > 5) {
            leaderboard_.resize(5);
        }
        data_.leaderboard = leaderboard_;
        data_.highScore = leaderboard_.front().score;
        state_ = GameState::GameOver;
        gameOver_.reset();
    }

    // --- Game scaffold -----------------------------------------------------
    void resetGame(Difficulty difficulty) {
        data_ = RenderData{};
        data_.difficulty = difficulty;
        data_.gridCols = Renderer::GRID_COLS;
        data_.gridRows = Renderer::GRID_ROWS;
        data_.level = 1;
        data_.score = 0;
        data_.highScore = leaderboard_.empty() ? 0 : leaderboard_.front().score;
        data_.snake = {{10, 10}, {9, 10}, {8, 10}};
        data_.obstacles.clear();

        direction_ = Command::Right;
        pendingDirection_ = Command::Right;
        tickIntervalMs_ = startTick(difficulty);
        accumulatorMs_ = 0.f;
        levelUpRemaining_ = 0.f;

        addObstacles(initialObstacles(difficulty));
        placeFood();
        state_ = GameState::Playing;
    }

    void update(float dt) {
        if (levelUpRemaining_ > 0.f) {
            levelUpRemaining_ -= dt;
            if (levelUpRemaining_ <= 0.f) {
                data_.showLevelUp = false;
            }
        }

        if (state_ != GameState::Playing) {
            return;
        }

        accumulatorMs_ += dt * 1000.f;
        while (accumulatorMs_ >= tickIntervalMs_ && state_ == GameState::Playing) {
            accumulatorMs_ -= tickIntervalMs_;
            step();
        }
    }

    void step() {
        if (data_.snake.empty()) {
            return;
        }
        direction_ = pendingDirection_;

        Cell head = data_.snake.front();
        int dx = 0;
        int dy = 0;
        switch (direction_) {
            case Command::Up:
                dy = -1;
                break;
            case Command::Down:
                dy = 1;
                break;
            case Command::Left:
                dx = -1;
                break;
            case Command::Right:
                dx = 1;
                break;
            default:
                break;
        }

        const Cell next{head.x + dx, head.y + dy};

        // Wall collision (FR-19)
        if (next.x < 0 || next.x >= data_.gridCols || next.y < 0 ||
            next.y >= data_.gridRows) {
            triggerGameOver();
            return;
        }

        const bool ate = (next == data_.food);

        // Self collision (FR-20). The tail cell frees up unless we grow.
        const std::size_t limit =
            ate ? data_.snake.size()
                : (data_.snake.size() > 1 ? data_.snake.size() - 1 : 0);
        for (std::size_t i = 0; i < limit; ++i) {
            if (data_.snake[i] == next) {
                triggerGameOver();
                return;
            }
        }

        // Obstacle collision (FR-21)
        for (const Cell& obstacle : data_.obstacles) {
            if (obstacle == next) {
                triggerGameOver();
                return;
            }
        }

        data_.snake.insert(data_.snake.begin(), next);
        if (ate) {
            data_.score += 10;
            if (data_.score > data_.highScore) {
                data_.highScore = data_.score;
            }
            placeFood();
            checkLevelUp();
        } else {
            data_.snake.pop_back();
        }
    }

    void checkLevelUp() {
        if (data_.level >= kMaxLevel || data_.score < data_.level * 50) {
            return;
        }
        ++data_.level;
        tickIntervalMs_ = std::max(kMinTickMs, tickIntervalMs_ - 10.f);
        addObstacles(2);
        data_.showLevelUp = true;
        levelUpRemaining_ = 1.f;
    }

    void triggerGameOver() {
        if (data_.score > data_.highScore) {
            data_.highScore = data_.score;
        }
        const bool qualifies =
            data_.score > 0 &&
            (leaderboard_.size() < 5 ||
             data_.score > leaderboard_.back().score);
        if (qualifies) {
            scoreEntry_.reset();
            state_ = GameState::ScoreEntry;
        } else {
            gameOver_.reset();
            state_ = GameState::GameOver;
        }
    }

    bool isOccupied(const Cell& cell) const {
        for (const Cell& c : data_.snake) {
            if (c == cell) return true;
        }
        for (const Cell& c : data_.obstacles) {
            if (c == cell) return true;
        }
        return data_.food == cell;
    }

    Cell randomEmptyCell() {
        std::uniform_int_distribution<int> dx(0, data_.gridCols - 1);
        std::uniform_int_distribution<int> dy(0, data_.gridRows - 1);
        for (int attempt = 0; attempt < 500; ++attempt) {
            Cell cell{dx(rng_), dy(rng_)};
            if (!isOccupied(cell)) {
                return cell;
            }
        }
        return Cell{-1, -1};
    }

    void placeFood() {
        const Cell cell = randomEmptyCell();
        data_.food = cell;
    }

    void addObstacles(int count) {
        for (int i = 0; i < count; ++i) {
            const Cell cell = randomEmptyCell();
            if (cell.x >= 0) {
                data_.obstacles.push_back(cell);
            }
        }
    }

    // --- Rendering ---------------------------------------------------------
    void render() {
        window_.clear(sf::Color(18, 22, 28));
        switch (state_) {
            case GameState::MainMenu:
                menu_.draw();
                break;
            case GameState::Playing:
                renderer_.drawGame(data_);
                break;
            case GameState::Paused:
                renderer_.drawGame(data_);
                renderer_.drawPausedOverlay();
                break;
            case GameState::GameOver:
                renderer_.drawGame(data_);
                gameOver_.draw(data_.score, data_.level);
                break;
            case GameState::HighScoreView:
                highScore_.draw(leaderboard_);
                break;
            case GameState::ScoreEntry:
                renderer_.drawGame(data_);
                scoreEntry_.draw(data_.score);
                break;
            default:
                break;
        }
        window_.display();
    }

    sf::RenderWindow window_;
    Renderer renderer_;
    InputHandler input_;
    MenuScreen menu_;
    GameOverScreen gameOver_;
    HighScoreScreen highScore_;
    ScoreEntryOverlay scoreEntry_;

    GameState state_ = GameState::MainMenu;
    RenderData data_;
    std::vector<ScoreEntry> leaderboard_;

    Command direction_ = Command::Right;
    Command pendingDirection_ = Command::Right;
    float tickIntervalMs_ = kEasyTickMs;
    float accumulatorMs_ = 0.f;
    float levelUpRemaining_ = 0.f;

    std::mt19937 rng_;
};

} // namespace snake

int main() {
    snake::Application app;
    app.run();
    return 0;
}
