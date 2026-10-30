#include "ScoreManager.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

namespace snake {
namespace {
bool validInitials(const std::string& initials) {
    if (initials.empty() || initials.size() > 3) return false;
    return std::all_of(initials.begin(), initials.end(), [](unsigned char c) {
        return c >= 'A' && c <= 'Z';
    });
}
} // namespace

void ScoreManager::addScore(const std::string& initials, int score) {
    if (!validInitials(initials) || score < 0) return;
    scores_.push_back({initials, score});
    sortAndLimit();
}
const std::vector<ScoreEntry>& ScoreManager::getTopScores() const { return scores_; }

bool ScoreManager::isTopScore(int score) const {
    if (score <= 0) return false;
    return scores_.size() < MAX_SCORES || score > scores_.back().score;
}
void ScoreManager::sortAndLimit() {
    std::stable_sort(scores_.begin(), scores_.end(),
        [](const ScoreEntry& a, const ScoreEntry& b) { return a.score > b.score; });
    if (scores_.size() > MAX_SCORES) scores_.resize(MAX_SCORES);
}
bool ScoreManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file) return false;
    for (const auto& entry : scores_) {
        file << entry.initials << ' ' << entry.score << '\n';
        if (!file) return false;
    }
    file.flush();
    return file.good();
}
bool ScoreManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return false;
    std::vector<ScoreEntry> loaded;
    std::string initials;
    int score = 0;
    while (file >> initials) {
        if (!(file >> score) || !validInitials(initials) || score < 0) return false;
        loaded.push_back({initials, score});
        if (loaded.size() > 1000) return false;
    }
    if (!file.eof()) return false;
    std::stable_sort(loaded.begin(), loaded.end(),
        [](const ScoreEntry& a, const ScoreEntry& b) { return a.score > b.score; });
    if (loaded.size() > MAX_SCORES) loaded.resize(MAX_SCORES);
    scores_.swap(loaded);
    return true;
}
} // namespace snake
