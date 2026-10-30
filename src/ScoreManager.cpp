#include "ScoreManager.h"

#include <algorithm>
#include <fstream>
#include <limits>
#include <string>

namespace snake {

void ScoreManager::addScore(const std::string& initials, int score)
{
    if (score < 0 || initials.empty())
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
    std::stable_sort(scores_.begin(), scores_.end(),
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });

    if (scores_.size() > MAX_SCORES)
        scores_.resize(MAX_SCORES);
}

bool ScoreManager::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);

    if (!file)
        return false;

    for (const auto& entry : scores_)
        file << entry.initials << ' ' << entry.score << '\n';

    return file.good();
}

bool ScoreManager::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
        return false;

    std::vector<ScoreEntry> loaded;
    std::string initials;
    int score;

    while (file >> initials >> score) {
        if (score < 0 || initials.empty())
            return false;

        loaded.push_back({initials, score});
    }

    if (!file.eof())
        return false;

    scores_ = std::move(loaded);
    sortAndLimit();

    return true;
}

}
