#pragma once

#include "Types.h"

#include <optional>
#include <vector>

namespace snake {

class Snake {
public:
    explicit Snake(int gridCols = 20, int gridRows = 20);

    void reset();
    void reset(int gridCols, int gridRows);

    // Returns false for non-direction commands and forbidden reversals.
    bool setDirection(Command requested);
    std::optional<Cell> nextHeadPosition() const;
    // Advances one cell. A growing move keeps the tail; an empty snake does nothing.
    std::optional<Cell> move(bool grow = false);

    const std::vector<Cell>& body() const noexcept { return body_; }
    Command direction() const noexcept { return direction_; }
    int gridCols() const noexcept { return gridCols_; }
    int gridRows() const noexcept { return gridRows_; }

private:
    int gridCols_;
    int gridRows_;
    Command direction_ = Command::Right;
    std::vector<Cell> body_;
};

} // namespace snake
