#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

ScoreManager::ScoreManager(const std::string& filename) : filename(filename) {
    LoadScores();
}

void ScoreManager::LoadScores() {
    scores.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "LoadScores: Could not open " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines or lines with only whitespace
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }

        std::stringstream ss(line);
        std::string name;
        int score;
        
        // Try to read name and score
        // This assumes format: Name Score
        // If name contains spaces, this simple extraction might fail or split it.
        // For robustness, let's assume the LAST token is the score, and everything before is the name.
        
        // Simple approach first:
        if (ss >> name >> score) {
            scores.push_back({name, score});
            // std::cout << "Loaded score: " << name << " - " << score << std::endl;
        } else {
            // std::cerr << "Failed to parse line: " << line << std::endl;
        }
    }
    // Ensure sorted
    std::sort(scores.begin(), scores.end(), std::greater<ScoreEntry>());
    std::cout << "Total scores loaded: " << scores.size() << std::endl;
}

void ScoreManager::SaveScore(const std::string& name, int score) {
    bool found = false;
    for (auto& entry : scores) {
        if (entry.name == name) {
            if (score > entry.score) {
                entry.score = score;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        scores.push_back({name, score});
    }

    std::sort(scores.begin(), scores.end(), std::greater<ScoreEntry>());

    // Write back to file
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : scores) {
            file << entry.name << " " << entry.score << "\n";
        }
        std::cout << "Saved scores to " << filename << std::endl;
    } else {
        std::cerr << "Failed to open " << filename << " for writing!" << std::endl;
    }
}

const std::vector<ScoreEntry>& ScoreManager::GetLeaderboard() const {
    return scores;
}
