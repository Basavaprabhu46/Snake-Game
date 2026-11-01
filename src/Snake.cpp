#include "Snake.h"

#include <stdexcept>

namespace snake {
namespace {
bool isDirection(Command c) {
    return c == Command::Up || c == Command::Down ||
           c == Command::Left || c == Command::Right;
}
bool isOpposite(Command a, Command b) {
    return (a == Command::Up && b == Command::Down) ||
           (a == Command::Down && b == Command::Up) ||
           (a == Command::Left && b == Command::Right) ||
           (a == Command::Right && b == Command::Left);
}
Cell delta(Command direction) {
    switch (direction) {
        case Command::Up: return {0, -1};
        case Command::Down: return {0, 1};
        case Command::Left: return {-1, 0};
        case Command::Right: return {1, 0};
        default: return {0, 0};
    }
}
void validateDimensions(int cols, int rows) {
    if (cols <= 0 || rows <= 0) throw std::invalid_argument("Snake grid dimensions must be positive");
    if (cols < 4 || rows < 1) throw std::invalid_argument("Snake grid cannot fit the initial body");
}
} // namespace

Snake::Snake(int gridCols, int gridRows) : gridCols_(gridCols), gridRows_(gridRows) {
    reset();
}

void Snake::reset() {
    validateDimensions(gridCols_, gridRows_);
    direction_ = Command::Right;
    const int headX = gridCols_ / 2;
    const int headY = gridRows_ / 2;
    body_ = {{headX, headY}, {headX - 1, headY}, {headX - 2, headY}};
}

void Snake::reset(int gridCols, int gridRows) {
    validateDimensions(gridCols, gridRows);
    gridCols_ = gridCols;
    gridRows_ = gridRows;
    reset();
}

bool Snake::setDirection(Command requested) {
    if (!isDirection(requested) || body_.empty() || isOpposite(direction_, requested)) return false;
    direction_ = requested;
    return true;
}

std::optional<Cell> Snake::nextHeadPosition() const {
    if (body_.empty()) return std::nullopt;
    const Cell d = delta(direction_);
    return Cell{body_.front().x + d.x, body_.front().y + d.y};
}

std::optional<Cell> Snake::move(bool grow) {
    const auto nextPosition = nextHeadPosition();
    if (!nextPosition) return std::nullopt;
    const Cell next = *nextPosition;
    body_.insert(body_.begin(), next);
    if (!grow) body_.pop_back();
    return next;
}

} // namespace snake
