#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameEngine.hpp"
#include "IInputHandler.hpp"
#include "ObstacleManager.hpp"
#include "TreasureManager.hpp"
#include "ShipManager.hpp"
#include "BoardMap.hpp"
#include "GameConstants.hpp"

using ::testing::Return;
using ::testing::_;

class MockInputHandler : public IInputHandler {
public:
    MOCK_METHOD(GameDirection, readInput, (), (override));
    MOCK_METHOD(bool, isRestartPressed, (), (override));
    MOCK_METHOD(bool, isQuitPressed, (), (override));
};

class MockObstacleManager : public ObstacleManager {
public:
    MockObstacleManager() : ObstacleManager(GameConstants::MAP_WIDTH, GameConstants::MAP_HEIGHT) {}
    MOCK_METHOD(void, UpdateObstacles, (), (override));
    MOCK_METHOD(void, SpawnObstacle, (int, int), (override));
};

TEST(GameEngineTest, Initialization) {
    auto mockInput = std::make_shared<MockInputHandler>();
    auto mockObs = std::make_unique<MockObstacleManager>();
    auto treasureMgr = std::make_unique<TreasureManager>(GameConstants::MAP_WIDTH, GameConstants::MAP_HEIGHT);
    auto shipMgr = std::make_unique<ShipManager>(10, 10, "Test");
    auto map = std::make_unique<BoardMap>(GameConstants::MAP_WIDTH, GameConstants::MAP_HEIGHT);
    
    GameEngine game(mockInput, std::move(mockObs), std::move(treasureMgr), std::move(shipMgr), std::move(map));
    game.Init("TestPlayer");
    
    EXPECT_FALSE(game.IsGameOver());
}

TEST(GameEngineTest, UpdateCallsObstacleManager) {
    auto mockInput = std::make_shared<MockInputHandler>();
    auto mockObs = std::make_unique<MockObstacleManager>();
    
    // Expect UpdateObstacles to be called once
    EXPECT_CALL(*mockObs, UpdateObstacles()).Times(1);
    
    auto treasureMgr = std::make_unique<TreasureManager>(GameConstants::MAP_WIDTH, GameConstants::MAP_HEIGHT);
    auto shipMgr = std::make_unique<ShipManager>(10, 10, "Test");
    auto map = std::make_unique<BoardMap>(GameConstants::MAP_WIDTH, GameConstants::MAP_HEIGHT);
    
    GameEngine game(mockInput, std::move(mockObs), std::move(treasureMgr), std::move(shipMgr), std::move(map));
    game.Init("TestPlayer");
    
    // Trigger update
    EXPECT_CALL(*mockInput, readInput()).WillOnce(Return(GameDirection::None));
    game.Update();
}
