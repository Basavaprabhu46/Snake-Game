#include <cassert>
#include <chrono>
#include <thread>
#include <iostream>
#include "LevelManager.hpp"
#include "Obstacle.hpp"
#include "InputHandler.hpp"

void runUnitAndSystemTests() {
    // UT-08 (FR-08): Tick interval varies by difficulty
    LevelManager easyLM(Difficulty::EASY);
    LevelManager medLM(Difficulty::MEDIUM);
    LevelManager hardLM(Difficulty::HARD);
    assert(easyLM.getTickIntervalMs() > medLM.getTickIntervalMs());
    assert(medLM.getTickIntervalMs() > hardLM.getTickIntervalMs());

    // UT-24 (FR-24): Level increments when score crosses threshold
    assert(medLM.getCurrentLevel() == 1);
    int gained = medLM.updateScore(LevelManager::POINTS_PER_LEVEL);
    assert(gained == 1 && medLM.getCurrentLevel() == 2);

    // UT-25 (FR-25): Speed increases (tick interval decreases) per level
    LevelManager speedLM(Difficulty::MEDIUM);
    int level1Tick = speedLM.getTickIntervalMs();
    speedLM.updateScore(LevelManager::POINTS_PER_LEVEL);
    int level2Tick = speedLM.getTickIntervalMs();
    assert(level2Tick < level1Tick);

    // UT-28 (FR-28): Max level capped at 10
    LevelManager maxLM(Difficulty::HARD);
    maxLM.updateScore(LevelManager::POINTS_PER_LEVEL * 25); // Huge score
    assert(maxLM.getCurrentLevel() == 10);

    // UT-29 (FR-29): Initial obstacles depend on difficulty
    std::vector<GridPos> snake = {{5, 5}, {4, 5}, {3, 5}};
    GridPos food{10, 10};
    ObstacleManager obsMgr(20, 20);
    obsMgr.initObstacles(Difficulty::EASY, snake, food);
    std::size_t easyCount = obsMgr.getObstacles().size();
    obsMgr.initObstacles(Difficulty::HARD, snake, food);
    std::size_t hardCount = obsMgr.getObstacles().size();
    assert(hardCount > easyCount);

    // UT-30 (FR-30): Exactly 2 obstacles added per level-up
    obsMgr.initObstacles(Difficulty::MEDIUM, snake, food);
    std::size_t beforeLevelUp = obsMgr.getObstacles().size();
    obsMgr.onLevelUp(1, snake, food);
    assert(obsMgr.getObstacles().size() == beforeLevelUp + 2);

    // UT-31 (FR-31): Obstacles only spawn on unoccupied cells
    for (const auto& obs : obsMgr.getObstacles()) {
        assert(!(obs == food));
        for (const auto& seg : snake) {
            assert(!(obs == seg));
        }
    }

    // UT-33 (FR-33): Random seed derived from system clock changes over time
    unsigned int seed1 = obsMgr.reseedFromSystemClock();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    unsigned int seed2 = obsMgr.reseedFromSystemClock();
    assert(seed1 != seed2);

    // ST-08 (NFR-02): Input latency <= 1 tick
    InputHandler input(Direction::RIGHT);
    input.enqueueDirection(Direction::UP);
    assert(input.consumeNextDirection() == Direction::UP); // Applied on very first tick

    std::cout << "All assigned tests (UT-08 to ST-09) passed successfully!\n";
}

int main() {
    runUnitAndSystemTests();
    return 0;
}