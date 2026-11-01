#include "Food.h"

#include <chrono>
#include <stdexcept>

namespace snake {
namespace {
void validateDimensions(int cols, int rows) {
    if (cols <= 0 || rows <= 0) throw std::invalid_argument("Food grid dimensions must be positive");
}
bool contains(const std::vector<Cell>& cells, Cell c) {
    for (const Cell& item : cells) if (item == c) return true;
    return false;
}
unsigned int randomSeed() {
    return static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}
} // namespace

Food::Food(int cols, int rows) : Food(cols, rows, randomSeed()) {}

Food::Food(int cols, int rows, unsigned int seed)
    : gridCols_(cols), gridRows_(rows), rng_(seed) {
    validateDimensions(cols, rows);
}

bool Food::respawn(const std::vector<Cell>& snake, const std::vector<Cell>& obstacles) {
    std::vector<Cell> freeCells;
    freeCells.reserve(static_cast<std::size_t>(gridCols_) * static_cast<std::size_t>(gridRows_));
    for (int y = 0; y < gridRows_; ++y) {
        for (int x = 0; x < gridCols_; ++x) {
            const Cell candidate{x, y};
            if (!contains(snake, candidate) && !contains(obstacles, candidate)) freeCells.push_back(candidate);
        }
    }
    if (freeCells.empty()) {
        position_.reset();
        return false;
    }
    std::uniform_int_distribution<std::size_t> pick(0, freeCells.size() - 1);
    position_ = freeCells[pick(rng_)];
    return true;
}

void Food::reset(const std::vector<Cell>& snake, const std::vector<Cell>& obstacles) {
    position_.reset();
    respawn(snake, obstacles);
}

std::optional<int> Food::consume(Cell head, const std::vector<Cell>& snake,
                                const std::vector<Cell>& obstacles) {
    if (!isAt(head)) return std::nullopt;
    respawn(snake, obstacles);
    return SCORE_AWARD;
}

} // namespace snake
