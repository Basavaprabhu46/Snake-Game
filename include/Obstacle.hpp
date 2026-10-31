#pragma once
#include <vector>
#include <random>
#include <chrono>
#include "LevelManager.hpp"

struct GridPos {
    int x;
    int y;
    bool operator==(const GridPos& other) const {
        return x == other.x && y == other.y;
    }
};

class ObstacleManager {
public:
    static constexpr int OBSTACLES_PER_LEVEL = 2; // FR-30: 2 obstacles per level

    // FR-33: Seeds PRNG from system clock by default
    ObstacleManager(int gridWidth, int gridHeight);

    // Explicit seed constructor for deterministic unit testing
    ObstacleManager(int gridWidth, int gridHeight, unsigned int explicitSeed);

    // FR-33: Re-seeds from current system clock
    unsigned int reseedFromSystemClock();
    unsigned int getLastSeed() const;

    // FR-29: Returns initial obstacle count for a difficulty level
    static int getInitialObstacleCount(Difficulty difficulty);

    // FR-29: Clears existing obstacles and spawns initial obstacles for difficulty
    void initObstacles(Difficulty difficulty,
                       const std::vector<GridPos>& snakeBody,
                       const GridPos& foodPos);

    // FR-30: Spawns 2 new obstacles per level gained
    void onLevelUp(int levelsGained,
                   const std::vector<GridPos>& snakeBody,
                   const GridPos& foodPos);

    // FR-31: Checks if a cell is completely free of snake, food, and obstacles
    bool isCellOccupied(const GridPos& pos,
                        const std::vector<GridPos>& snakeBody,
                        const GridPos& foodPos) const;

    bool hasObstacleAt(const GridPos& pos) const;
    const std::vector<GridPos>& getObstacles() const;

private:
    int gridWidth_;
    int gridHeight_;
    unsigned int lastSeed_;
    std::mt19937 rng_;
    std::vector<GridPos> obstacles_;

    bool spawnSingleObstacle(const std::vector<GridPos>& snakeBody,
                             const GridPos& foodPos);
};