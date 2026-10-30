add_executable(test_grid test_grid.cpp)

target_include_directories(test_grid
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)

add_test(NAME UT-04_GridInitialization COMMAND test_grid)


# UT-34 Top-5 leaderboard
add_executable(test_score_manager
    test_score_manager.cpp
    ${PROJECT_SOURCE_DIR}/src/ScoreManager.cpp
)

target_include_directories(test_score_manager
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)

add_test(NAME UT-34_Top5Leaderboard COMMAND test_score_manager)
