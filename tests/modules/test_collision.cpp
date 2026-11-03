#include "CollisionDetector.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
using snake::Cell;
using snake::CollisionDetector;
using snake::CollisionType;
using snake::Command;

[[noreturn]] void failCheck(const char* expression, const char* file, int line) {
    std::cerr << file << ':' << line << ": CHECK failed: " << expression << '\n';
    std::exit(EXIT_FAILURE);
}

#define CHECK(expression) \
    do { if (!(expression)) failCheck(#expression, __FILE__, __LINE__); } while (false)

void testWallCollisionOnEveryBoundary() {
    CollisionDetector detector(5, 5);
    CHECK(detector.checkTick({{2, 0}}, Command::Up).type == CollisionType::Wall);    // top
    CHECK(detector.checkTick({{2, 4}}, Command::Down).type == CollisionType::Wall);  // bottom
    CHECK(detector.checkTick({{0, 2}}, Command::Left).type == CollisionType::Wall);  // left
    CHECK(detector.checkTick({{4, 2}}, Command::Right).type == CollisionType::Wall); // right
}

void testSelfCollisionAndMovingTailException() {
    CollisionDetector detector(5, 5);
    const std::vector<Cell> body{{2, 2}, {2, 3}, {1, 3}, {1, 2}};

    CHECK(detector.checkNextPosition({1, 3}, body).type == CollisionType::Self);
    CHECK(detector.checkNextPosition({2, 1}, body).type == CollisionType::None);

    // The head moves left into the current tail cell, which leaves this tick.
    CHECK(detector.checkNextPosition({1, 2}, body).type == CollisionType::None);
    // Growth retains the tail, so the same destination is a self-collision.
    CHECK(detector.checkNextPosition({1, 2}, body, {}, true).type == CollisionType::Self);
}

void testObstacleAndTickChecks() {
    CollisionDetector detector(5, 5);
    const std::vector<Cell> body{{2, 2}, {2, 3}, {1, 3}, {1, 2}};
    const std::vector<Cell> obstacles{{3, 2}};
    CHECK(detector.checkNextPosition({3, 2}, body, obstacles).type == CollisionType::Obstacle);
    CHECK(detector.checkTick(body, Command::Right, obstacles).type == CollisionType::Obstacle);
    CHECK(detector.checkTick(body, Command::Up).type == CollisionType::None);
}

void testEmptyAndOneSegmentSnakes() {
    CollisionDetector detector(5, 5);
    CHECK(!detector.checkTick({}, Command::Right).collided());
    CHECK(detector.checkTick({{2, 2}}, Command::Right).type == CollisionType::None);
    CHECK(detector.checkTick({{0, 0}}, Command::Left).type == CollisionType::Wall);
}

void testInvalidDimensionsAndSmallGrid() {
    for (const auto dimensions : std::vector<std::pair<int, int>>{
             {0, 5}, {5, 0}, {-1, 5}, {5, -1}}) {
        bool rejected = false;
        try { CollisionDetector bad(dimensions.first, dimensions.second); }
        catch (const std::invalid_argument&) { rejected = true; }
        CHECK(rejected);
    }

    CollisionDetector oneCell(1, 1);
    CHECK(oneCell.checkNextPosition({0, 0}, {}).type == CollisionType::None);
}
} // namespace

int main() {
    testWallCollisionOnEveryBoundary();
    testSelfCollisionAndMovingTailException();
    testObstacleAndTickChecks();
    testEmptyAndOneSegmentSnakes();
    testInvalidDimensionsAndSmallGrid();
}
