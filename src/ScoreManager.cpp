#include "ScoreManager.h"

#include <algorithm>
#include <utility>

namespace snake {

void ScoreManager::addScore(const std::string& initials, int score)
{
    if (score < 0)
        return;

    scores_.push_back({initials, score});
    sortAndLimit();
}

const std::vector<ScoreEntry>& ScoreManager::getTopScores() const
{
    return scores_;
}

bool ScoreManager::isTopScore(int score) const
{
    if (score < 0)
        return false;

    if (scores_.size() < MAX_SCORES)
        return true;

    return score > scores_.back().score;
}

void ScoreManager::sortAndLimit()
{
    std::stable_sort(
        scores_.begin(),
        scores_.end(),
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        }
    );

    if (scores_.size() > MAX_SCORES)
        scores_.resize(MAX_SCORES);
}

}
