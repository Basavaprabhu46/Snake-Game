#include "Food.h"
#include "Snake.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
using snake::Cell;
using snake::Food;
using snake::Snake;

[[noreturn]] void failCheck(const char* expression, const char* file, int line) {
    std::cerr << file << ':' << line << ": CHECK failed: " << expression << '\n';
    std::exit(EXIT_FAILURE);
}

#define CHECK(expression) \
    do { if (!(expression)) failCheck(#expression, __FILE__, __LINE__); } while (false)

void testPlacementAvoidsOccupancyAndReset() {
    Food food(5, 5, 107u);
    CHECK(!food.position()); // Occupancy must be supplied before placement.
    const std::vector<Cell> body{{0, 0}, {0, 1}};
    const std::vector<Cell> obstacles{{1, 0}, {1, 1}};
    const bool initiallyPlaced = food.respawn(body, obstacles);
    CHECK(initiallyPlaced);
    CHECK(food.position().has_value());

    for (int i = 0; i < 500; ++i) {
        const bool placed = food.respawn(body, obstacles);
        CHECK(placed);
        CHECK(food.position().has_value());
        for (Cell occupied : body) CHECK(*food.position() != occupied);
        for (Cell occupied : obstacles) CHECK(*food.position() != occupied);
    }

    food.reset(body, obstacles);
    CHECK(food.position().has_value());
    for (Cell occupied : body) CHECK(*food.position() != occupied);
    for (Cell occupied : obstacles) CHECK(*food.position() != occupied);
}

void testRepeatedConsumptionAwardsTenPoints() {
    Food food(6, 6, 31u);
    std::vector<Cell> body{{0, 0}};
    const std::vector<Cell> obstacles{{5, 5}};

    for (int eaten = 0; eaten < 6; ++eaten) {
        const bool placed = food.respawn(body, obstacles);
        CHECK(placed);
        CHECK(food.position().has_value());
        const Cell target = *food.position();
        const Cell wrongHead = target == Cell{5, 4} ? Cell{4, 4} : Cell{5, 4};
        const auto wrongAward = food.consume(wrongHead, body, obstacles);
        CHECK(!wrongAward.has_value());
        CHECK(food.isAt(target));

        std::vector<Cell> movedBody = body;
        movedBody.insert(movedBody.begin(), target);
        const auto award = food.consume(target, movedBody, obstacles);
        CHECK(award.has_value());
        CHECK(*award == Food::SCORE_AWARD);
        CHECK(*award == 10);
        body = std::move(movedBody);
        if (food.position()) {
            for (Cell occupied : body) CHECK(*food.position() != occupied);
            for (Cell occupied : obstacles) CHECK(*food.position() != occupied);
        }
    }
}

void testSingleFreeCellAndFullBoard() {
    std::vector<Cell> almostFull;
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (x != 3 || y != 3) almostFull.push_back({x, y});
        }
    }
    Food constrained(4, 4, 3u);
    const bool singleCellPlaced = constrained.respawn(almostFull, {});
    CHECK(singleCellPlaced);
    CHECK((constrained.position() && *constrained.position() == Cell{3, 3}));

    const std::vector<Cell> full{{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    Food fullBoard(2, 2, 9u);
    const bool fullBoardPlaced = fullBoard.respawn(full, {});
    CHECK(!fullBoardPlaced);
    CHECK(!fullBoard.position());

    Food oneCell(1, 1, 4u);
    const bool oneCellPlaced = oneCell.respawn({}, {});
    CHECK(oneCellPlaced);
    CHECK((oneCell.position() && *oneCell.position() == Cell{0, 0}));
    const bool occupiedOneCellPlaced = oneCell.respawn({{0, 0}}, {});
    CHECK(!occupiedOneCellPlaced);
    CHECK(!oneCell.position());
}

void testFoodAndSnakeGrowthTogether() {
    Snake subject(4, 1);
    Food food(4, 1, 7u);
    const std::vector<Cell> obstacles;

    const auto next = subject.nextHeadPosition();
    CHECK(next.has_value());
    CHECK(*next == (Cell{3, 0}));
    const bool placed = food.respawn(subject.body(), obstacles);
    CHECK(placed);
    CHECK(food.isAt(*next)); // The next cell is the only unoccupied cell.

    const auto movedHead = subject.move(true);
    CHECK(movedHead.has_value());
    CHECK(*movedHead == *next);
    CHECK(subject.body().size() == 4);
    const auto award = food.consume(*movedHead, subject.body(), obstacles);
    CHECK(award.has_value());
    CHECK(*award == 10);
    CHECK(!food.position()); // The growing snake now fills the board.
}

void testInvalidDimensions() {
    for (const auto dimensions : std::vector<std::pair<int, int>>{
             {0, 5}, {5, 0}, {-1, 5}, {5, -1}}) {
        bool rejected = false;
        try { Food bad(dimensions.first, dimensions.second); }
        catch (const std::invalid_argument&) { rejected = true; }
        CHECK(rejected);
    }
}
} // namespace

int main() {
    testPlacementAvoidsOccupancyAndReset();
    testRepeatedConsumptionAwardsTenPoints();
    testSingleFreeCellAndFullBoard();
    testFoodAndSnakeGrowthTogether();
    testInvalidDimensions();
}
