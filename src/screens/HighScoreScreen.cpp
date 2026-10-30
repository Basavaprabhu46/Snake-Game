#include "HighScoreScreen.h"

#include <string>

#include "Renderer.h"

namespace snake {

namespace {
const sf::Color kText(232, 238, 245);
const sf::Color kAccent(250, 210, 70);
const sf::Color kMuted(150, 160, 175);
} // namespace

HighScoreScreen::HighScoreScreen(Renderer& renderer) : renderer_(renderer) {}

void HighScoreScreen::reset() { done_ = false; }

void HighScoreScreen::handleCommand(Command command) {
    if (command == Command::Back || command == Command::Confirm ||
        command == Command::Menu) {
        done_ = true;
    }
}

void HighScoreScreen::draw(const std::vector<ScoreEntry>& entries) const {
    renderer_.drawTextCentered("HIGH SCORES", 26, 120.f, kAccent);

    if (entries.empty()) {
        renderer_.drawTextCentered("No scores yet.", 12, 300.f, kMuted);
    } else {
        float y = 210.f;
        for (std::size_t i = 0; i < entries.size(); ++i) {
            const std::string row =
                std::to_string(i + 1) + ".  " + entries[i].initials + "   " +
                std::to_string(entries[i].score);
            renderer_.drawTextCentered(row, 14, y, kText);
            y += 52.f;
        }
    }

    renderer_.drawTextCentered("Press Esc to return", 9, 580.f, kMuted);
}

} // namespace snake
