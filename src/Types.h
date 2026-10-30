#pragma once

#include <string>
#include <vector>

namespace snake {

// ---------------------------------------------------------------------------
// Game-wide enums and data-only structs shared across modules.
// Keep these free of SFML types so core logic stays headless-testable.
// ---------------------------------------------------------------------------

enum class GameState {
    MainMenu,
    DifficultySelect,
    Playing,
    Paused,
    LevelTransition,
    ScoreEntry,
    GameOver,
    HighScoreView,
    Exit
};

enum class Difficulty { Easy, Medium, Hard };

enum class Command {
    None,
    Up,
    Down,
    Left,
    Right,
    Pause,
    Restart,
    Menu,
    Confirm,
    Back,
    Quit
};

struct Cell {
    int x = 0;
    int y = 0;

    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Cell& other) const { return !(*this == other); }
};

struct ScoreEntry {
    std::string initials;
    int score = 0;
};

// Snapshot that the Renderer consumes. It decouples rendering (this module's
// presentation layer) from the game-logic classes and keeps Renderer testable
// without constructing a full game.
struct RenderData {
    GameState state = GameState::MainMenu;
    int gridCols = 20;
    int gridRows = 20;
    std::vector<Cell> snake;         // head first
    Cell food{-1, -1};
    std::vector<Cell> obstacles;
    std::vector<ScoreEntry> leaderboard;
    int score = 0;
    int level = 1;
    int highScore = 0;
    bool showLevelUp = false;
    Difficulty difficulty = Difficulty::Easy;
};

} // namespace snake
