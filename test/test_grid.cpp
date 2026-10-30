#include "Types.h"
#include <cassert>
#include <iostream>

int main()
{
    snake::RenderData data{};

    assert(data.gridCols == 20);
    assert(data.gridRows == 20);

    std::cout << "UT-04 passed: Grid is 20x20\n";
    return 0;
}
