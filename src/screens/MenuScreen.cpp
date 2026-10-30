#include "MenuScreen.h"

#include <string>

#include "Renderer.h"

namespace snake {

namespace {
const sf::Color kText(232, 238, 245);
const sf::Color kAccent(250, 210, 70);
const sf::Color kMuted(150, 160, 175);
} // namespace

MenuScreen::MenuScreen(Renderer& renderer) : renderer_(renderer) {}

void MenuScreen::reset() {
    mode_ = Mode::Main;
    mainIndex_ = 0;
    diffIndex_ = 0;
    action_ = MenuAction::None;
}

void MenuScreen::handleCommand(Command command) {
    switch (mode_) {
        case Mode::Main:
            if (command == Command::Up) {
                mainIndex_ = (mainIndex_ + kMainItems - 1) % kMainItems;
            } else if (command == Command::Down) {
                mainIndex_ = (mainIndex_ + 1) % kMainItems;
            } else if (command == Command::Confirm) {
                switch (mainIndex_) {
                    case 0:
                        mode_ = Mode::Difficulty;
                        diffIndex_ = 0;
                        break;
                    case 1:
                        action_ = MenuAction::ViewHighScores;
                        break;
                    case 2:
                        mode_ = Mode::Instructions;
                        break;
                    case 3:
                    default:
                        action_ = MenuAction::Exit;
                        break;
                }
            } else if (command == Command::Back) {
                action_ = MenuAction::Exit;
            }
            break;

        case Mode::Difficulty:
            if (command == Command::Up) {
                diffIndex_ =
                    (diffIndex_ + kDifficultyItems - 1) % kDifficultyItems;
            } else if (command == Command::Down) {
                diffIndex_ = (diffIndex_ + 1) % kDifficultyItems;
            } else if (command == Command::Confirm) {
                switch (diffIndex_) {
                    case 0:
                        action_ = MenuAction::StartEasy;
                        break;
                    case 1:
                        action_ = MenuAction::StartMedium;
                        break;
                    case 2:
                    default:
                        action_ = MenuAction::StartHard;
                        break;
                }
            } else if (command == Command::Back) {
                mode_ = Mode::Main;
            }
            break;

        case Mode::Instructions:
            if (command == Command::Back || command == Command::Confirm) {
                mode_ = Mode::Main;
            }
            break;
    }
}

void MenuScreen::draw() const {
    switch (mode_) {
        case Mode::Main:
            drawMain();
            break;
        case Mode::Difficulty:
            drawDifficulty();
            break;
        case Mode::Instructions:
            drawInstructions();
            break;
    }
}

void MenuScreen::drawMain() const {
    renderer_.drawTextCentered("SNAKE GAME", 34, 120.f, kAccent);
    renderer_.drawTextCentered("Team 11  |  PES University", 10, 175.f, kMuted);

    static const char* kItems[kMainItems] = {"START GAME", "HIGH SCORES",
                                             "INSTRUCTIONS", "EXIT"};

    const float startY = 270.f;
    for (int i = 0; i < kMainItems; ++i) {
        const bool selected = (i == mainIndex_);
        std::string label = kItems[i];
        if (selected) {
            label = "> " + label;
        }
        renderer_.drawTextCentered(label, 18, startY + static_cast<float>(i) * 55.f,
                                   selected ? kAccent : kText);
    }

    renderer_.drawTextCentered("Use Up/Down to navigate, Enter to select", 9,
                               560.f, kMuted);
}

void MenuScreen::drawDifficulty() const {
    renderer_.drawTextCentered("SELECT DIFFICULTY", 24, 170.f, kAccent);

    static const char* kItems[kDifficultyItems] = {"EASY", "MEDIUM", "HARD"};
    static const char* kDesc[kDifficultyItems] = {"Slow start, no obstacles",
                                                  "Medium speed, 5 obstacles",
                                                  "Fast start, 10 obstacles"};

    const float startY = 280.f;
    for (int i = 0; i < kDifficultyItems; ++i) {
        const bool selected = (i == diffIndex_);
        std::string label = kItems[i];
        if (selected) {
            label = "> " + label;
        }
        renderer_.drawTextCentered(label, 18, startY + static_cast<float>(i) * 60.f,
                                   selected ? kAccent : kText);
        renderer_.drawTextCentered(kDesc[i], 9,
                                   startY + static_cast<float>(i) * 60.f + 28.f,
                                   kMuted);
    }

    renderer_.drawTextCentered("Enter to start, Esc to go back", 9, 580.f,
                               kMuted);
}

void MenuScreen::drawInstructions() const {
    renderer_.drawTextCentered("INSTRUCTIONS", 24, 140.f, kAccent);

    static const char* kLines[] = {
        "Arrow keys / WASD   -  Move snake",
        "P                   -  Pause / Resume",
        "R                   -  Restart (Game Over)",
        "M                   -  Main Menu (Game Over)",
        "Enter               -  Confirm",
        "Esc                 -  Back",
    };

    const float startY = 240.f;
    for (int i = 0; i < 6; ++i) {
        renderer_.drawTextCentered(kLines[i], 10,
                                   startY + static_cast<float>(i) * 44.f, kText);
    }

    renderer_.drawTextCentered("Press Enter or Esc to return", 9, 560.f, kMuted);
}

} // namespace snake
