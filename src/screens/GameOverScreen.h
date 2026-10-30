#pragma once

#include "Types.h"

namespace snake {

class Renderer;

enum class GameOverAction { None, Restart, MainMenu };

// ---------------------------------------------------------------------------
// GameOverScreen  (FR-45, FR-46)
//
// Shows 'GAME OVER', the final score and highest level, and offers two
// options: [R] Restart and [M] Main Menu.
// ---------------------------------------------------------------------------
class GameOverScreen {
public:
    explicit GameOverScreen(Renderer& renderer);

    void reset();
    void handleCommand(Command command);
    void draw(int score, int level) const;

    GameOverAction action() const { return action_; }
    void clearAction() { action_ = GameOverAction::None; }

private:
    Renderer& renderer_;
    GameOverAction action_ = GameOverAction::None;
};

} // namespace snake
