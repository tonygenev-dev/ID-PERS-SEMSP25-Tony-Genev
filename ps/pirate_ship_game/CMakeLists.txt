cmake_minimum_required(VERSION 3.11)
project(pirate_ship_game LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
    GIT_TAG main      # or use a release tag like 'v6.1.1'
)

FetchContent_MakeAvailable(ftxui)

add_library(pirate_ship_lib
    entities/Ship.cpp
    entities/Obstacle.cpp
    entities/Treasure.cpp
    engine/ObstacleManager.cpp
    engine/TreasureManager.cpp
    engine/ShipManager.cpp
    engine/BoardMap.cpp
    engine/GameEngine.cpp
    engine/ScoreManager.cpp
    ui/GameApplication.cpp
)
target_include_directories(pirate_ship_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/input
    ${CMAKE_CURRENT_SOURCE_DIR}/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)
target_link_libraries(pirate_ship_lib PUBLIC ftxui::screen ftxui::dom ftxui::component)

add_executable(pirate_ship_game main.cpp)
target_link_libraries(pirate_ship_game PRIVATE pirate_ship_lib)

enable_testing()

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(pirate_ship_tests
    tests/ObstacleManagerTests.cpp
    tests/GameEngineTests.cpp
    tests/ScoreManagerTests.cpp
    tests/ShipManagerTests.cpp # Added
)
target_link_libraries(pirate_ship_tests PRIVATE pirate_ship_lib gtest_main gmock)
include(GoogleTest)
gtest_discover_tests(pirate_ship_tests)
