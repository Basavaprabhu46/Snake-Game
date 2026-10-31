#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <deque>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class InputHandler {
public:
    static constexpr std::size_t MAX_BUFFER_SIZE = 2;

    explicit InputHandler(Direction initialDir = Direction::RIGHT)
        : currentDir_(initialDir) {}

    void reset(Direction initialDir = Direction::RIGHT) {
        inputQueue_.clear();
        currentDir_ = initialDir;
    }

    // Called every frame in the SFML event loop
    void handleKeyPress(sf::Keyboard::Key key) {
    Direction requested = currentDir_;
    switch (key) {
            case sf::Keyboard::Up:
            case sf::Keyboard::W: requested = Direction::UP; break;
            case sf::Keyboard::Down:
            case sf::Keyboard::S: requested = Direction::DOWN; break;
            case sf::Keyboard::Left:
            case sf::Keyboard::A: requested = Direction::LEFT; break;
            case sf::Keyboard::Right:
            case sf::Keyboard::D: requested = Direction::RIGHT; break;
        default: return;
    }
    enqueueDirection(requested);
}

    // Direct enqueue helper (used by unit/system test ST-08)
    void enqueueDirection(Direction requested) {
        if (inputQueue_.size() >= MAX_BUFFER_SIZE) {
            return;
        }
        Direction referenceDir = inputQueue_.empty() ? currentDir_ : inputQueue_.back();
        if (requested != referenceDir && !isOpposite(referenceDir, requested)) {
            inputQueue_.push_back(requested);
        }
    }

    // Called once per game tick — guarantees latency <= 1 tick (NFR-02)
    Direction consumeNextDirection() {
        if (!inputQueue_.empty()) {
            currentDir_ = inputQueue_.front();
            inputQueue_.pop_front();
        }
        return currentDir_;
    }

private:
    Direction currentDir_;
    std::deque<Direction> inputQueue_;

    static bool isOpposite(Direction a, Direction b) {
        return (a == Direction::UP && b == Direction::DOWN) ||
               (a == Direction::DOWN && b == Direction::UP) ||
               (a == Direction::LEFT && b == Direction::RIGHT) ||
               (a == Direction::RIGHT && b == Direction::LEFT);
    }
};