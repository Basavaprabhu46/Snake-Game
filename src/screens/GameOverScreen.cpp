#include "GameOverScreen.h"

#include "Renderer.h"

namespace snake {

namespace {
const sf::Color kText(232, 238, 245);
const sf::Color kAccent(250, 210, 70);
const sf::Color kDanger(240, 90, 90);
} // namespace

GameOverScreen::GameOverScreen(Renderer& renderer) : renderer_(renderer) {}

void GameOverScreen::reset() { action_ = GameOverAction::None; }

void GameOverScreen::handleCommand(Command command) {
    switch (command) {
        case Command::Restart:
        case Command::Confirm:  // Enter on the R option
            action_ = GameOverAction::Restart;
            break;
        case Command::Menu:
        case Command::Back:
            action_ = GameOverAction::MainMenu;
            break;
        default:
            break;
    }
}

void GameOverScreen::draw(int score, int level) const {
    renderer_.drawOverlay(sf::Color(0, 0, 0, 190));
    renderer_.drawTextCentered("GAME OVER", 32, 175.f, kDanger);
    renderer_.drawTextCentered("Score: " + std::to_string(score), 16, 250.f,
                               kText);
    renderer_.drawTextCentered("Level: " + std::to_string(level), 16, 290.f,
                               kText);
    renderer_.drawTextCentered("[R] Restart", 14, 370.f, kAccent);
    renderer_.drawTextCentered("[M] Main Menu", 14, 410.f, kAccent);
}

} // namespace snake
