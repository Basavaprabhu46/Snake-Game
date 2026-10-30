#include "Types.h"
#include <cassert>
#include <iostream>

int main()
{
    // UT-04: Grid initialization
    snake::RenderData gridData{};
    assert(gridData.gridCols == 20);
    assert(gridData.gridRows == 20);

    std::cout << "UT-04 passed: Grid is 20x20\n";

    // UT-06: Score and level defaults for a new game
    snake::RenderData gameData{};
    assert(gameData.score == 0);
    assert(gameData.level == 1);

    std::cout << "UT-06 passed: Score is 0 and level is 1\n";

    return 0;
}
