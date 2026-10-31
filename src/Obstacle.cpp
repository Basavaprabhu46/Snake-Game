#include "Obstacle.hpp"
#include <algorithm>

ObstacleManager::ObstacleManager(int gridWidth, int gridHeight)
    : gridWidth_(gridWidth), gridHeight_(gridHeight), lastSeed_(0) {
    reseedFromSystemClock();
    obstacles_.reserve(64); // Pre-allocate for NFR-05 memory efficiency
}

ObstacleManager::ObstacleManager(int gridWidth, int gridHeight, unsigned int explicitSeed)
    : gridWidth_(gridWidth),
      gridHeight_(gridHeight),
      lastSeed_(explicitSeed),
      rng_(explicitSeed) {
    obstacles_.reserve(64);
}

unsigned int ObstacleManager::reseedFromSystemClock() {
    // FR-33: Obtain seed from std::chrono::system_clock
    auto now = std::chrono::system_clock::now().time_since_epoch();
    lastSeed_ = static_cast<unsigned int>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(now).count()
    );
    rng_.seed(lastSeed_);
    return lastSeed_;
}

unsigned int ObstacleManager::getLastSeed() const {
    return lastSeed_;
}

int ObstacleManager::getInitialObstacleCount(Difficulty difficulty) {
    // FR-29: Initial obstacle counts scaled by difficulty
    switch (difficulty) {
        case Difficulty::EASY:   return 2;
        case Difficulty::MEDIUM: return 5;
        case Difficulty::HARD:   return 8;
        default:                 return 5;
    }
}

void ObstacleManager::initObstacles(Difficulty difficulty,
                                    const std::vector<GridPos>& snakeBody,
                                    const GridPos& foodPos) {
    obstacles_.clear();
    int count = getInitialObstacleCount(difficulty);
    for (int i = 0; i < count; ++i) {
        spawnSingleObstacle(snakeBody, foodPos);
    }
}

void ObstacleManager::onLevelUp(int levelsGained,
                                const std::vector<GridPos>& snakeBody,
                                const GridPos& foodPos) {
    if (levelsGained <= 0) return;

    // FR-30: Add 2 obstacles per level increment
    int toSpawn = levelsGained * OBSTACLES_PER_LEVEL;
    for (int i = 0; i < toSpawn; ++i) {
        spawnSingleObstacle(snakeBody, foodPos);
    }
}

bool ObstacleManager::hasObstacleAt(const GridPos& pos) const {
    return std::find(obstacles_.begin(), obstacles_.end(), pos) != obstacles_.end();
}

bool ObstacleManager::isCellOccupied(const GridPos& pos,
                                     const std::vector<GridPos>& snakeBody,
                                     const GridPos& foodPos) const {
    if (pos == foodPos) {
        return true;
    }
    if (std::find(snakeBody.begin(), snakeBody.end(), pos) != snakeBody.end()) {
        return true;
    }
    if (hasObstacleAt(pos)) {
        return true;
    }
    return false;
}

bool ObstacleManager::spawnSingleObstacle(const std::vector<GridPos>& snakeBody,
                                          const GridPos& foodPos) {
    // Collect all unoccupied cells to guarantee O(1) conflict-free selection (FR-31)
    std::vector<GridPos> freeCells;
    freeCells.reserve(gridWidth_ * gridHeight_);

    for (int y = 0; y < gridHeight_; ++y) {
        for (int x = 0; x < gridWidth_; ++x) {
            GridPos candidate{x, y};
            if (!isCellOccupied(candidate, snakeBody, foodPos)) {
                freeCells.push_back(candidate);
            }
        }
    }

    if (freeCells.empty()) {
        return false;
    }

    std::uniform_int_distribution<std::size_t> dist(0, freeCells.size() - 1);
    obstacles_.push_back(freeCells[dist(rng_)]);
    return true;
}

const std::vector<GridPos>& ObstacleManager::getObstacles() const {
    return obstacles_;
}