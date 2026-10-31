#include "LevelManager.hpp"

LevelManager::LevelManager(Difficulty difficulty)
    : difficulty_(difficulty), currentLevel_(MIN_LEVEL) {}

void LevelManager::reset(Difficulty difficulty) {
    difficulty_ = difficulty;
    currentLevel_ = MIN_LEVEL;
}

int LevelManager::getBaseTickIntervalMs(Difficulty difficulty) {
    // FR-08: Base tick interval determined by difficulty
    switch (difficulty) {
        case Difficulty::EASY:   return 150;
        case Difficulty::MEDIUM: return 120;
        case Difficulty::HARD:   return 90;
        default:                 return 120;
    }
}

int LevelManager::updateScore(int currentScore) {
    if (currentScore < 0) {
        currentScore = 0;
    }

    // FR-24: Increment level at every POINTS_PER_LEVEL threshold
    int targetLevel = MIN_LEVEL + (currentScore / POINTS_PER_LEVEL);

    // FR-28: Enforce hard cap at MAX_LEVEL (10)
    targetLevel = std::min(targetLevel, MAX_LEVEL);

    if (targetLevel > currentLevel_) {
        int levelsGained = targetLevel - currentLevel_;
        currentLevel_ = targetLevel;
        return levelsGained;
    }
    return 0;
}

int LevelManager::getTickIntervalMs() const {
    // FR-08 & FR-25: Base interval minus speed reduction per level above 1
    int baseInterval = getBaseTickIntervalMs(difficulty_);
    int reduction = (currentLevel_ - MIN_LEVEL) * SPEED_STEP_MS;
    return std::max(MIN_TICK_INTERVAL_MS, baseInterval - reduction);
}

int LevelManager::getCurrentLevel() const {
    return currentLevel_;
}

Difficulty LevelManager::getDifficulty() const {
    return difficulty_;
}