#pragma once
#include <string>
#include <vector>
#include <algorithm>

struct ScoreEntry {
    std::string name;
    int score;
    
    // For sorting descending
    bool operator>(const ScoreEntry& other) const {
        return score > other.score;
    }
};

class ScoreManager {
    std::string filename;
    std::vector<ScoreEntry> scores;

public:
    ScoreManager(const std::string& filename = "scores.txt");
    
    void LoadScores();
    void SaveScore(const std::string& name, int score);
    const std::vector<ScoreEntry>& GetLeaderboard() const;
};
