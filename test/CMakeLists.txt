add_executable(test_grid test_grid.cpp)

target_include_directories(test_grid
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)

add_test(NAME UT-04_GridInitialization COMMAND test_grid)
