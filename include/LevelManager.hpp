#pragma once
#include <algorithm>

enum class Difficulty {
    EASY = 0,
    MEDIUM = 1,
    HARD = 2
};

class LevelManager {
public:
    static constexpr int MIN_LEVEL = 1;
    static constexpr int MAX_LEVEL = 10;              // FR-28: Max level 10
    static constexpr int POINTS_PER_LEVEL = 50;       // FR-24: Threshold per level
    static constexpr int SPEED_STEP_MS = 8;           // FR-25: Speed increase per level
    static constexpr int MIN_TICK_INTERVAL_MS = 40;   // Safety floor for tick interval

    explicit LevelManager(Difficulty difficulty = Difficulty::MEDIUM);

    void reset(Difficulty difficulty);

    // FR-24: Updates level based on score threshold.
    // Returns the number of levels gained on this update (0 if no level-up).
    int updateScore(int currentScore);

    // FR-08 & FR-25: Returns current tick interval (ms) based on difficulty and level
    int getTickIntervalMs() const;

    int getCurrentLevel() const;
    Difficulty getDifficulty() const;
    static int getBaseTickIntervalMs(Difficulty difficulty);

private:
    Difficulty difficulty_;
    int currentLevel_;
};