#include "Types.h"
#include <cassert>
#include <iostream>
#include "HudText.h"

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
    // UT-18: HUD high-score display
snake::RenderData hudData{};
hudData.highScore = 500;

assert(snake::highScoreLabel(hudData) == "HIGH 500");

std::cout << "UT-18 passed: High score displayed correctly\n";

    return 0;
}
