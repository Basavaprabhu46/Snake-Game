#pragma once

#include "Types.h"

#include <optional>
#include <random>
#include <vector>

namespace snake {

class Food {
public:
    static constexpr int SCORE_AWARD = 10;

    explicit Food(int gridCols = 20, int gridRows = 20);
    Food(int gridCols, int gridRows, unsigned int seed);

    // Construction leaves food unplaced because occupancy is unknown. Call this
    // with the current snake and obstacle cells to place one item safely.
    // Returns false and clears the position when the board has no free cell.
    bool respawn(const std::vector<Cell>& snake,
                 const std::vector<Cell>& obstacles);
    void reset(const std::vector<Cell>& snake,
               const std::vector<Cell>& obstacles);

    std::optional<Cell> position() const noexcept { return position_; }
    bool isAt(Cell cell) const noexcept { return position_ && *position_ == cell; }

    // Returns +10 when head consumes food, otherwise nullopt. Respawn considers
    // the supplied post-move snake body, so newly grown segments remain blocked.
    std::optional<int> consume(Cell head, const std::vector<Cell>& snake,
                               const std::vector<Cell>& obstacles);

    int gridCols() const noexcept { return gridCols_; }
    int gridRows() const noexcept { return gridRows_; }

private:
    int gridCols_;
    int gridRows_;
    std::mt19937 rng_;
    std::optional<Cell> position_;
};

} // namespace snake
