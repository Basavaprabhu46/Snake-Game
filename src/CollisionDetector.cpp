#include "CollisionDetector.h"

#include <stdexcept>

namespace snake {

CollisionDetector::CollisionDetector(int cols, int rows) : gridCols_(cols), gridRows_(rows) {
    if (cols <= 0 || rows <= 0) throw std::invalid_argument("Collision grid dimensions must be positive");
}

CollisionResult CollisionDetector::checkNextPosition(Cell next,
        const std::vector<Cell>& body, const std::vector<Cell>& obstacles,
        bool growing) const {
    if (next.x < 0 || next.x >= gridCols_ || next.y < 0 || next.y >= gridRows_)
        return {CollisionType::Wall, next};

    const std::size_t bodyLimit = !growing && !body.empty() ? body.size() - 1 : body.size();
    for (std::size_t i = 0; i < bodyLimit; ++i)
        if (body[i] == next) return {CollisionType::Self, next};

    for (const Cell& obstacle : obstacles)
        if (obstacle == next) return {CollisionType::Obstacle, next};

    return {CollisionType::None, next};
}

CollisionResult CollisionDetector::checkTick(const std::vector<Cell>& body, Command direction,
        const std::vector<Cell>& obstacles, bool growing) const {
    if (body.empty()) return {};
    int dx = 0, dy = 0;
    switch (direction) {
        case Command::Up: dy = -1; break;
        case Command::Down: dy = 1; break;
        case Command::Left: dx = -1; break;
        case Command::Right: dx = 1; break;
        default: return {};
    }
    return checkNextPosition({body.front().x + dx, body.front().y + dy}, body, obstacles, growing);
}

} // namespace snake
