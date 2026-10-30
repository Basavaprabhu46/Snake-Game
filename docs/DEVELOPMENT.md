# Development Guide — Snake Game (Team 11)

> Course: UE24CS341A — Software Engineering | PES University

## Implementation status (as of 30 Oct 2026)

**Implemented — UI / presentation layer (owner: Basava Prabhu, PES2UG24CS109):**

| File | Responsibility | Requirements |
|---|---|---|
| `src/Types.h` | Shared enums / `RenderData` snapshot / `Command` | — |
| `src/InputHandler.*` | Keyboard event → game command | FR-02, FR-09, FR-44 |
| `src/Renderer.*` | Grid, snake, food, obstacles, HUD, overlays | FR-12, FR-17, FR-26, FR-27, FR-32, FR-39, FR-42 |
| `src/screens/MenuScreen.*` | Main menu (4 options) + difficulty select | FR-01, FR-02, FR-03 |
| `src/screens/GameOverScreen.*` | Game Over + Restart / Main Menu | FR-45, FR-46 |
| `src/screens/HighScoreScreen.*` | Ranked leaderboard view | FR-38 |
| `src/screens/ScoreEntryOverlay.*` | 3-initial entry (A–Z) | FR-37 |
| `src/main.cpp` | Runnable harness (scaffold) | — |

**Pending — owned by other team members (per SAD):**

| Module | Owner |
|---|---|
| `Game` / state machine | Basavaraj Ramesh (PES2UG24CS110) |
| `Snake`, `Food`, `CollisionDetector` | Nikil Kumar Reddy (PES2UG24CS107) |
| `LevelManager`, `Obstacle` | Kodandapaani Reddy (PES2UG24CS108) |
| `ScoreManager` | Basavaraj Ramesh (PES2UG24CS110) |

The snake loop in `main.cpp` is a **scaffold** so the UI can be demonstrated end
to end; it will be replaced by the `GameEngine` module in Sprint-2.

## Build

### Linux (used by CI)

```bash
sudo apt-get install -y cmake g++ libsfml-dev
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/SnakeGame
```

### macOS

```bash
brew install cmake sfml@2
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/sfml@2
cmake --build build --parallel
./build/SnakeGame
```

## Controls

| Key | Action |
|---|---|
| ↑ ↓ ← → / W A S D | Move / menu navigation |
| Enter / Space | Confirm |
| P | Pause / Resume |
| R | Restart (Game Over) |
| M | Main Menu (Game Over) |
| Esc | Back |

## Contribution workflow

1. Pick an issue from the **Sprint-1 / Sprint-2** milestone.
2. Create a branch: `git checkout -b feat/FR-XX-short-name`.
3. Commit using conventional messages, e.g. `feat(snake): start position (FR-05)`.
4. Push and open a **pull request** against `main`.
5. The repo owner reviews and merges; **CI must be green**.

## Backlog

All **48 FRs** and **5 NFRs** from the SRS are tracked as GitHub issues, labelled
by module (`module:*`), typed (`type:FR` / `type:NFR`), estimated with story
points (`sp:*`), and planned into the `Sprint-1` / `Sprint-2` milestones.
