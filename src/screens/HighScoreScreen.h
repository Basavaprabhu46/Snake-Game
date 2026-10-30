#pragma once

#include <vector>

#include "Types.h"

namespace snake {

class Renderer;

// ---------------------------------------------------------------------------
// HighScoreScreen  (FR-38)
//
// Displays the full leaderboard (rank, initials, score) sorted descending.
// ---------------------------------------------------------------------------
class HighScoreScreen {
public:
    explicit HighScoreScreen(Renderer& renderer);

    void reset();
    void handleCommand(Command command);
    void draw(const std::vector<ScoreEntry>& entries) const;

    bool done() const { return done_; }

private:
    Renderer& renderer_;
    bool done_ = false;
};

} // namespace snake
