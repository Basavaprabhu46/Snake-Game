#pragma once

#include "Types.h"

#include <optional>
#include <vector>

namespace snake {

enum class CollisionType { None, Wall, Self, Obstacle };

struct CollisionResult {
    CollisionType type = CollisionType::None;
    std::optional<Cell> position;
    bool collided() const noexcept { return type != CollisionType::None; }
};

class CollisionDetector {
public:
    CollisionDetector(int gridCols, int gridRows);

    CollisionResult checkNextPosition(Cell nextHead,
                                      const std::vector<Cell>& snake,
                                      const std::vector<Cell>& obstacles = {},
                                      bool growing = false) const;

    // Convenience tick API: calculates the next head cell and applies the same
    // wall, self, and obstacle rules. Empty snakes have no next head/collision.
    CollisionResult checkTick(const std::vector<Cell>& snake, Command direction,
                              const std::vector<Cell>& obstacles = {},
                              bool growing = false) const;

private:
    int gridCols_;
    int gridRows_;
};

} // namespace snake
