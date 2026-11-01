cmake_minimum_required(VERSION 3.16)
project(SnakeModulesTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
set(MODULE_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/../../src/Snake.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../src/Food.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../src/CollisionDetector.cpp)
foreach(suite IN ITEMS snake food collision)
    set(test_target ${suite}_tests)
    add_executable(${test_target} test_${suite}.cpp ${MODULE_SOURCES})
    target_include_directories(${test_target} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../src)
    add_test(NAME ${test_target} COMMAND ${test_target})
endforeach()
