cmake_minimum_required(VERSION 3.16)
project(SnakeGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------
option(BUILD_TESTS "Build unit tests (GoogleTest)" OFF)
option(ENABLE_COVERAGE "Enable gcov/lcov coverage instrumentation" OFF)
option(ENABLE_SANITIZERS "Enable ASan/UBSan" OFF)

if(ENABLE_COVERAGE)
  add_compile_options(--coverage -O0 -g)
  add_link_options(--coverage)
endif()

if(ENABLE_SANITIZERS)
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endif()

# ---------------------------------------------------------------------------
# SFML 2.x (2.5 / 2.6). CI installs libsfml-dev from apt.
# ---------------------------------------------------------------------------
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------
set(SNAKE_SOURCES
    src/main.cpp
    src/InputHandler.cpp
    src/Renderer.cpp
    src/ScoreManager.cpp
    src/screens/MenuScreen.cpp
    src/screens/GameOverScreen.cpp
    src/screens/HighScoreScreen.cpp
    src/screens/ScoreEntryOverlay.cpp
)

add_executable(SnakeGame ${SNAKE_SOURCES})
target_include_directories(SnakeGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(SnakeGame PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_definitions(SnakeGame PRIVATE
    SNAKE_ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

# Copy assets next to the binary so the game also runs from the build folder.
add_custom_command(TARGET SnakeGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:SnakeGame>/assets)

# ---------------------------------------------------------------------------
# Tests (optional; owned by the testing phase)
# ---------------------------------------------------------------------------
if(BUILD_TESTS)
  enable_testing()
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
    add_subdirectory(test)
  endif()
endif()
