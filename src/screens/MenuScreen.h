#pragma once

#include "Types.h"

namespace snake {

class Renderer;

enum class MenuAction {
    None,
    StartEasy,
    StartMedium,
    StartHard,
    ViewHighScores,
    Exit
};

// ---------------------------------------------------------------------------
// MenuScreen  (FR-01, FR-02, FR-03)
//
// Main menu with exactly four options (Start Game, High Scores, Instructions,
// Exit) and a difficulty-selection sub-screen (Easy / Medium / Hard). Keyboard
// navigation is driven by Command::Up / Down / Confirm / Back.
// ---------------------------------------------------------------------------
class MenuScreen {
public:
    explicit MenuScreen(Renderer& renderer);

    void reset();
    void handleCommand(Command command);
    void draw() const;

    MenuAction action() const { return action_; }
    void clearAction() { action_ = MenuAction::None; }

private:
    enum class Mode { Main, Difficulty, Instructions };

    void drawMain() const;
    void drawDifficulty() const;
    void drawInstructions() const;

    Renderer& renderer_;
    Mode mode_ = Mode::Main;
    int mainIndex_ = 0;
    int diffIndex_ = 0;
    MenuAction action_ = MenuAction::None;

    static constexpr int kMainItems = 4;
    static constexpr int kDifficultyItems = 3;
};

} // namespace snake
