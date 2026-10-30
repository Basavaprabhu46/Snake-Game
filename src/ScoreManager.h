#pragma once

#include "Types.h"
#include <string>
#include <vector>

namespace snake {

class ScoreManager {
public:
    static constexpr std::size_t MAX_SCORES = 5;

    void addScore(const std::string& initials, int score);
    const std::vector<ScoreEntry>& getTopScores() const;
    bool isTopScore(int score) const;

    bool saveToFile(const std::string& filename = "scores.dat") const;
    bool loadFromFile(const std::string& filename = "scores.dat");

private:
    std::vector<ScoreEntry> scores_;

    void sortAndLimit();
};

}
