#include "ScoreEntryOverlay.h"

#include "Renderer.h"

namespace snake {

ScoreEntryOverlay::ScoreEntryOverlay(Renderer& renderer) : renderer_(renderer) {}

void ScoreEntryOverlay::reset() {
    initials_.clear();
    submitted_ = false;
}

void ScoreEntryOverlay::handleText(unsigned int unicode) {
    if (initials_.size() >= kMaxInitials) {
        return;
    }
    if (unicode >= 'a' && unicode <= 'z') {
        initials_.push_back(static_cast<char>(unicode - 'a' + 'A'));
    } else if (unicode >= 'A' && unicode <= 'Z') {
        initials_.push_back(static_cast<char>(unicode));
    }
}

void ScoreEntryOverlay::handleCommand(Command command) {
    if (command == Command::Back) {
        if (!initials_.empty()) {
            initials_.pop_back();
        }
    } else if (command == Command::Confirm) {
        if (!initials_.empty()) {
            submitted_ = true;
        }
    }
}

void ScoreEntryOverlay::draw(int score) const {
    renderer_.drawScoreEntry(initials_, score);
}

} // namespace snake
