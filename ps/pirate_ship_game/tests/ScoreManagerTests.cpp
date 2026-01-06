#include <gtest/gtest.h>
#include "ScoreManager.hpp"
#include <fstream>
#include <cstdio>

class ScoreManagerTest : public ::testing::Test {
protected:
    std::string testFilename = "test_scores.txt";

    void SetUp() override {
        // Ensure clean state
        std::remove(testFilename.c_str());
    }

    void TearDown() override {
        // Cleanup
        std::remove(testFilename.c_str());
    }
};

TEST_F(ScoreManagerTest, SaveAndLoadScore) {
    ScoreManager sm(testFilename);
    sm.SaveScore("Player1", 100);
    
    auto scores = sm.GetLeaderboard();
    ASSERT_EQ(scores.size(), 1);
    EXPECT_EQ(scores[0].name, "Player1");
    EXPECT_EQ(scores[0].score, 100);
}

TEST_F(ScoreManagerTest, UpdateExistingScore) {
    ScoreManager sm(testFilename);
    sm.SaveScore("Player1", 100);
    sm.SaveScore("Player1", 200); // Should update
    
    auto scores = sm.GetLeaderboard();
    ASSERT_EQ(scores.size(), 1);
    EXPECT_EQ(scores[0].name, "Player1");
    EXPECT_EQ(scores[0].score, 200);
}

TEST_F(ScoreManagerTest, DontUpdateWithLowerScore) {
    ScoreManager sm(testFilename);
    sm.SaveScore("Player1", 200);
    sm.SaveScore("Player1", 100); // Should NOT update
    
    auto scores = sm.GetLeaderboard();
    ASSERT_EQ(scores.size(), 1);
    EXPECT_EQ(scores[0].name, "Player1");
    EXPECT_EQ(scores[0].score, 200);
}

TEST_F(ScoreManagerTest, LoadMalformedFile) {
    // Create a file with bad data
    {
        std::ofstream file(testFilename);
        file << "Valid 100\n";
        file << "InvalidLine\n";
        file << " 200\n"; // The case that caused issues
        file << "\n";
        file << "AlsoValid 50\n";
    }
    
    ScoreManager sm(testFilename);
    auto scores = sm.GetLeaderboard();
    
    // Should have parsed the 2 valid lines
    ASSERT_EQ(scores.size(), 2);
    EXPECT_EQ(scores[0].name, "Valid");
    EXPECT_EQ(scores[0].score, 100);
    EXPECT_EQ(scores[1].name, "AlsoValid");
    EXPECT_EQ(scores[1].score, 50);
}

TEST_F(ScoreManagerTest, Sorting) {
    ScoreManager sm(testFilename);
    sm.SaveScore("A", 10);
    sm.SaveScore("B", 30);
    sm.SaveScore("C", 20);
    
    auto scores = sm.GetLeaderboard();
    ASSERT_EQ(scores.size(), 3);
    EXPECT_EQ(scores[0].name, "B"); // 30
    EXPECT_EQ(scores[1].name, "C"); // 20
    EXPECT_EQ(scores[2].name, "A"); // 10
}
