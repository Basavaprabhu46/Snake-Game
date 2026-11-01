#include "Snake.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {
using snake::Cell;
using snake::Command;
using snake::Snake;

[[noreturn]] void failCheck(const char* expression, const char* file, int line) {
    std::cerr << file << ':' << line << ": CHECK failed: " << expression << '\n';
    std::exit(EXIT_FAILURE);
}

#define CHECK(expression) \
    do { if (!(expression)) failCheck(#expression, __FILE__, __LINE__); } while (false)

void testStartAndReset() {
    Snake subject;
    const std::vector<Cell> initial{{10, 10}, {9, 10}, {8, 10}};
    CHECK(subject.body() == initial);
    CHECK(subject.direction() == Command::Right);

    const bool accepted = subject.setDirection(Command::Up);
    CHECK(accepted);
    const auto moved = subject.move(true);
    CHECK(moved.has_value());
    subject.reset();
    CHECK(subject.body() == initial);
    CHECK(subject.direction() == Command::Right);
}

void testReverseRejectionPreservesDirection() {
    Snake subject;
    CHECK(subject.direction() == Command::Right);
    bool accepted = subject.setDirection(Command::Left);
    CHECK(!accepted);
    CHECK(subject.direction() == Command::Right);

    accepted = subject.setDirection(Command::Up);
    CHECK(accepted);
    accepted = subject.setDirection(Command::Down);
    CHECK(!accepted);
    CHECK(subject.direction() == Command::Up);

    accepted = subject.setDirection(Command::Left);
    CHECK(accepted);
    accepted = subject.setDirection(Command::Right);
    CHECK(!accepted);
    CHECK(subject.direction() == Command::Left);

    accepted = subject.setDirection(Command::Down);
    CHECK(accepted);
    accepted = subject.setDirection(Command::Up);
    CHECK(!accepted);
    CHECK(subject.direction() == Command::Down);

    accepted = subject.setDirection(Command::Right);
    CHECK(accepted);
    accepted = subject.setDirection(Command::Left);
    CHECK(!accepted);
    CHECK(subject.direction() == Command::Right);
    accepted = subject.setDirection(Command::None);
    CHECK(!accepted);
    CHECK(subject.direction() == Command::Right);
}

void testCompleteBodyMovement() {
    Snake subject;
    bool accepted = subject.setDirection(Command::Up);
    CHECK(accepted);
    const auto upHead = subject.move();
    CHECK(upHead.has_value());
    CHECK(*upHead == (Cell{10, 9}));
    CHECK((subject.body() == std::vector<Cell>{{10, 9}, {10, 10}, {9, 10}}));

    accepted = subject.setDirection(Command::Left);
    CHECK(accepted);
    const auto leftHead = subject.move();
    CHECK(leftHead.has_value());
    CHECK(*leftHead == (Cell{9, 9}));
    CHECK((subject.body() == std::vector<Cell>{{9, 9}, {10, 9}, {10, 10}}));

    accepted = subject.setDirection(Command::Down);
    CHECK(accepted);
    const auto downHead = subject.move();
    CHECK(downHead.has_value());
    CHECK(*downHead == (Cell{9, 10}));
    CHECK((subject.body() == std::vector<Cell>{{9, 10}, {9, 9}, {10, 9}}));

    accepted = subject.setDirection(Command::Right);
    CHECK(accepted);
    const auto rightHead = subject.move();
    CHECK(rightHead.has_value());
    CHECK(*rightHead == (Cell{10, 10}));
    CHECK((subject.body() == std::vector<Cell>{{10, 10}, {9, 10}, {9, 9}}));
}

void testGrowthAndDimensions() {
    Snake subject;
    const auto oldSize = subject.body().size();
    const auto grownHead = subject.move(true);
    CHECK(grownHead.has_value());
    CHECK(subject.body().size() == oldSize + 1);

    bool rejected = false;
    try { Snake badCols(0, 20); } catch (const std::invalid_argument&) { rejected = true; }
    CHECK(rejected);
    rejected = false;
    try { Snake badRows(20, -1); } catch (const std::invalid_argument&) { rejected = true; }
    CHECK(rejected);
    rejected = false;
    try { Snake tooNarrow(3, 1); } catch (const std::invalid_argument&) { rejected = true; }
    CHECK(rejected);

    Snake minimumValid(4, 1);
    CHECK((minimumValid.body() == std::vector<Cell>{{2, 0}, {1, 0}, {0, 0}}));
}
} // namespace

int main() {
    testStartAndReset();
    testReverseRejectionPreservesDirection();
    testCompleteBodyMovement();
    testGrowthAndDimensions();
}
