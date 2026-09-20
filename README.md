# 🐍 Snake Game

> A feature-rich 2D Snake Game built in **C++17** with **SFML 2.5+**  
> Mini-Project | UE24CS341A – Software Engineering | PES University, Bangalore

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Build & Run](#build--run)
- [Controls](#controls)
- [Gameplay](#gameplay)
- [Project Structure](#project-structure)
- [Team](#team)
- [CI/CD Pipeline](#cicd-pipeline)
- [Testing](#testing)
- [Academic Context](#academic-context)

---

## About

A fully playable, graphical Snake Game developed as part of the Software Engineering course (UE24CS341A) at PES University. The project demonstrates the complete Software Development Life Cycle — from requirements and design through implementation, testing, and CI/CD integration.

The game is rendered using SFML and supports progressive difficulty, static obstacles, a persistent high-score leaderboard, and pause/resume functionality.

---

## Features

| Feature | Description |
|---|---|
| **Core Gameplay** | Classic snake movement on a 20×20 grid with real-time keyboard control |
| **Multiple Difficulty Levels** | Easy / Medium / Hard — controls starting speed and obstacle count |
| **Level Progression** | Score thresholds trigger level-ups; speed increases and new obstacles are added each level (up to Level 10) |
| **Obstacles** | Static obstacle tiles placed randomly; density increases per level |
| **Collision Detection** | Wall, self-collision, and obstacle detection — all trigger Game Over |
| **High Score Leaderboard** | Top-5 scores persisted to `scores.dat`; survives across sessions |
| **Pause / Resume** | Press `P` to pause; exact game state is preserved on resume |
| **HUD** | Live score, current level, and session high score displayed at all times |
| **Game Over Screen** | Final score and level shown; options to restart or return to main menu |

---

## Prerequisites

| Dependency | Version | Notes |
|---|---|---|
| GCC / G++ | 9.4+ | C++17 support required (`-std=c++17`) |
| SFML | 2.5.1+ | Modules needed: Window, Graphics, System |
| CMake | 3.16+ | Build system |
| GoogleTest | 1.14+ | Unit testing (auto-fetched by CMake or install via apt) |
| gcov + lcov | Any | Bundled with GCC; lcov for HTML coverage reports |

### Install SFML

**Ubuntu / Debian**
```bash
sudo apt-get install libsfml-dev
```

**macOS (Homebrew)**
```bash
brew install sfml
```

**Windows**
Download the SFML 2.5.1 SDK from https://www.sfml-dev.org/download.php and set `SFML_DIR` in CMake.

---

## Build & Run

```bash
# Clone the repository
git clone https://github.com/<your-org>/snake-game-team11.git
cd snake-game-team11

# Configure
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --parallel

# Run
./build/SnakeGame
```

> **Windows (MSVC):**  
> Open the generated Visual Studio solution in `build/` or use  
> `cmake --build build --config Release`

---

## Controls

| Key | Action |
|---|---|
| `↑` / `W` | Move Up |
| `↓` / `S` | Move Down |
| `←` / `A` | Move Left |
| `→` / `D` | Move Right |
| `P` | Pause / Resume |
| `R` | Restart (from Game Over screen) |
| `M` | Main Menu (from Game Over screen) |
| `Enter` | Confirm selection in menus |
| `↑` / `↓` | Navigate menus |
| `Esc` | Exit to Main Menu |

---

## Gameplay

1. Launch the game → **Main Menu** appears.
2. Select **Start Game** → choose difficulty: **Easy**, **Medium**, or **Hard**.
3. Control the snake to eat food (red item). Each food item:
   - Adds **10 points** to your score.
   - Grows the snake by **1 segment**.
4. Reach the score threshold to **Level Up** — speed increases and new obstacles appear.
5. Avoid hitting **walls**, your own **body**, and **obstacle tiles**.
6. On Game Over, enter your initials if you make the top-5 leaderboard.

**Scoring**

| Event | Points |
|---|---|
| Food consumed | +10 |
| Level up threshold | `Level × 50` |
| Maximum level | 10 |

**Difficulty Parameters**

| Difficulty | Start Speed (tick) | Initial Obstacles |
|---|---|---|
| Easy | 150 ms | 0 |
| Medium | 100 ms | 5 |
| Hard | 70 ms | 10 |

Speed increases by 10 ms per level up, floored at 40 ms.

---

## Project Structure

```
snake-game-team11/
├── src/
│   ├── main.cpp                # Entry point
│   ├── Game.cpp / Game.h       # Game loop and state machine
│   ├── Snake.cpp / Snake.h     # Snake body, direction, growth
│   ├── Food.cpp / Food.h       # Food placement logic
│   ├── Obstacle.cpp / Obstacle.h   # Obstacle generation
│   ├── CollisionDetector.cpp / .h  # Wall / self / obstacle detection
│   ├── LevelManager.cpp / .h   # Level thresholds, speed control
│   ├── ScoreManager.cpp / .h   # Leaderboard, scores.dat I/O
│   ├── InputHandler.cpp / .h   # Keyboard event translation
│   ├── Renderer.cpp / .h       # SFML rendering (grid, HUD, screens)
│   └── screens/
│       ├── MenuScreen.cpp / .h
│       ├── GameOverScreen.cpp / .h
│       ├── HighScoreScreen.cpp / .h
│       └── ScoreEntryOverlay.cpp / .h
├── test/
│   ├── cases/                  # Filled Phase-3 test case docs
│   ├── data/                   # scores.dat fixtures (valid, corrupt, empty)
│   ├── test_snake.cpp
│   ├── test_food.cpp
│   ├── test_collision.cpp
│   ├── test_level.cpp
│   ├── test_obstacle.cpp
│   └── test_score_manager.cpp
├── assets/
│   └── fonts/                  # Open-source font(s) used in the game
├── docs/
│   ├── SRS_SnakeGame_Team11.docx
│   ├── STP_SnakeGame_Team11.docx
│   └── HighLevelDesign.docx
├── scores.dat                  # Auto-generated on first run
├── CMakeLists.txt
├── Jenkinsfile
└── README.md
```

---

## Team

**Team 11 | Section B | PES University, Bangalore**  
Course: UE24CS341A – Software Engineering (2025)

| Name | SRN | Role | Module Ownership |
|---|---|---|---|
| Baddela Guru Nikil Kumar Reddy | PES2UG24CS107 | Test Engineer / Dev | `Snake`, `Food`, `CollisionDetector` |
| Bandiatmakuru Kodandapaani Reddy | PES2UG24CS108 | QA Lead / Dev | `LevelManager`, `Obstacle`, CI Pipeline |
| Basava Prabhu | PES2UG24CS109 | Developer | `InputHandler`, `Renderer`, Menu Screens |
| Basavaraj Ramesh | PES2UG24CS110 | Product Owner / Dev | `ScoreManager`, `GameEngine`, State Machine |

---

## CI/CD Pipeline

The project uses **Jenkins** connected to this GitHub repository via webhook.

**Pipeline stages (defined in `Jenkinsfile`):**

```
Checkout → Build (CMake) → Unit Tests (GoogleTest) → Coverage (gcov/lcov) → Static Analysis (SonarQube)
```

| Stage | Tool | Pass Criteria |
|---|---|---|
| Build | CMake + GCC | Zero errors or warnings |
| Unit Tests | GoogleTest | All UT-01 to UT-48 pass |
| Coverage | gcov / lcov | ≥ 70% branch coverage on logic modules |
| Static Analysis | SonarQube | 0 critical / blocker findings |

Every **pull request to `main`** must pass all pipeline stages before merge.

---

## Testing

### Run unit tests locally

```bash
# Build with tests enabled
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
cmake --build build --parallel

# Run all GoogleTest suites
cd build && ctest --output-on-failure
```

### Generate coverage report

```bash
# After running tests with a Debug+coverage build
lcov --capture --directory build/ --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
genhtml coverage.info --output-directory coverage-report/
# Open coverage-report/index.html in a browser
```

### Test suites

| Suite | ID Range | Count | Method |
|---|---|---|---|
| Unit Tests | UT-01 – UT-48 | 48 | GoogleTest (automated) |
| Integration Tests | IT-01 – IT-09 | 9 | GoogleTest + manual |
| System Tests | ST-01 – ST-09 | 9 | Manual (Phase-3 template) |

Full test case documentation is in `test/cases/` and in `docs/STP_SnakeGame_Team11.docx`.

---

## Academic Context

This project is submitted as part of:

- **Course:** UE24CS341A – Software Engineering
- **Programme:** B.Tech. Computer Science and Engineering, V Semester
- **Institution:** PES University, Bengaluru – 560085
- **Submission period:** August – December 2025

All code is original work by Team 11. LLM tools were used for assistance; every team member understands and can explain all submitted code. Third-party assets (fonts) are open-source with attribution in `assets/`.

---

> *For bugs or evaluation queries, open a GitHub Issue in this repository.*
