#include "Types.h"
#include <cassert>
#include <iostream>

int main()
{
    // UT-04: Grid initialization
    snake::RenderData gridData{};
    assert(gridData.gridCols == 20);
    assert(gridData.gridRows == 20);
    std::cout << "UT-04 passed\n";

    // UT-06: Score and level initialization
    snake::RenderData gameData{};
    assert(gameData.score == 0);
    assert(gameData.level == 1);
    std::cout << "UT-06 passed\n";

    return 0;
}
