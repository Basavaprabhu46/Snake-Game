#pragma once

#include <string>

#include "Types.h"

namespace snake {

class Renderer;

// ---------------------------------------------------------------------------
// ScoreEntryOverlay  (FR-37)
//
// Prompts the player to enter up to 3 alphabetic initials when their score
// qualifies for the leaderboard. Only A-Z is accepted.
// ---------------------------------------------------------------------------
class ScoreEntryOverlay {
public:
    explicit ScoreEntryOverlay(Renderer& renderer);

    void reset();
    void handleCommand(Command command);
    void handleText(unsigned int unicode);
    void draw(int score) const;

    bool submitted() const { return submitted_; }
    const std::string& initials() const { return initials_; }

private:
    Renderer& renderer_;
    std::string initials_;
    bool submitted_ = false;

    static constexpr std::size_t kMaxInitials = 3;
};

} // namespace snake
