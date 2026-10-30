#include "ScoreManager.h"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    const std::string validFile = "ut_scores_valid.dat";
    const std::string corruptFile = "ut_scores_corrupt.dat";

    snake::ScoreManager manager;
    manager.addScore("AAA", 100);
    manager.addScore("BBB", 500);
    manager.addScore("CCC", 200);
    manager.addScore("DDD", 400);
    manager.addScore("EEE", 300);
    manager.addScore("FFF", 600);

    const auto& scores = manager.getTopScores();
    assert(scores.size() == 5);
    assert(scores[0].score == 600 && scores[1].score == 500);
    assert(scores[2].score == 400 && scores[3].score == 300);
    assert(scores[4].score == 200);
    assert(manager.isTopScore(700));
    assert(!manager.isTopScore(100));
    assert(!manager.isTopScore(0));

    // FR-35: persist and restore the leaderboard.
    assert(manager.saveToFile(validFile));
    snake::ScoreManager restored;
    assert(restored.loadFromFile(validFile));
    assert(restored.getTopScores().size() == 5);
    assert(restored.getTopScores()[0].initials == "FFF");
    assert(restored.getTopScores()[0].score == 600);

    // FR-36: reject corrupt data without replacing existing in-memory scores.
    {
        std::ofstream bad(corruptFile);
        bad << "AAA 100\nBAD_SCORE\n";
    }
    assert(!restored.loadFromFile(corruptFile));
    assert(restored.getTopScores().size() == 5);
    assert(restored.getTopScores()[0].score == 600);

    std::remove(validFile.c_str());
    std::remove(corruptFile.c_str());
    std::cout << "UT-34/35/36 passed: leaderboard, persistence and corrupt-file handling\n";
    return 0;
}
