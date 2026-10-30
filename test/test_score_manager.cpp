#include "ScoreManager.h"
#include <cassert>
#include <iostream>

int main()
{
    snake::ScoreManager manager;

    manager.addScore("AAA", 100);
    manager.addScore("BBB", 500);
    manager.addScore("CCC", 200);
    manager.addScore("DDD", 400);
    manager.addScore("EEE", 300);
    manager.addScore("FFF", 600);

    const auto& scores = manager.getTopScores();

    assert(scores.size() == 5);
    assert(scores[0].score == 600);
    assert(scores[1].score == 500);
    assert(scores[2].score == 400);
    assert(scores[3].score == 300);
    assert(scores[4].score == 200);

    assert(manager.isTopScore(700));
    assert(!manager.isTopScore(100));

    std::cout << "UT-34 passed: Top-5 leaderboard works\n";

    return 0;
}
