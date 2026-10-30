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

private:
    std::vector<ScoreEntry> scores_;
    void sortAndLimit();
};

}
