# Snake Game — Project Review Pitch

> **Team 11 | UE24CS341A Software Engineering | PES University**
>
> Use this as a speaking guide. Do not read every word; open the linked
> evidence as you explain each part.

---

## 1. Opening — 30 seconds

> Good morning. Our project is a feature-rich 2D Snake Game built in C++17
> using SFML. We followed the software-engineering process from requirements
> through backlog planning, two sprints, implementation, pull requests,
> automated build checks, and unit tests.
>
> Our final backlog contains **53 stories**: **48 functional requirements**
> and **5 non-functional requirements**. All 53 are assigned and closed in
> GitHub. The game builds successfully through GitHub Actions.

**Open:** repository README, then GitHub → Issues.

---

## 2. SRS — what we planned to build — 1 minute

**Open:** `SRS.docx`, section **5.1.3 Functional Requirements**.

> We started with the SRS. It defines the expected behavior of the game using
> numbered requirement IDs, from FR-01 to FR-48. This gave us a traceable list
> of features instead of vague tasks.

### Requirement groups

| SRS requirements | What they cover |
|---|---|
| FR-01 to FR-03 | Main menu, navigation, difficulty selection |
| FR-04 to FR-23 | Grid, snake movement, food, score, growth and collisions |
| FR-24 to FR-33 | Levels, speed changes and obstacles |
| FR-34 to FR-39 | Top-five leaderboard, score saving/loading and display |
| FR-40 to FR-48 | Pause/resume, Game Over, restart and score qualification |
| NFR-01 to NFR-05 | Frame rate, input response, startup time, file I/O and memory |

> For example, FR-34 says the game must maintain a top-five leaderboard.
> We implemented that as the `ScoreManager` module and tested it. This is how
> we connect the SRS to actual code.

---

## 3. User stories / GitHub backlog — 1 minute

**Open:** GitHub → **Issues**. Show labels and one issue such as FR-34.

> We converted every SRS requirement into one GitHub issue, which acts as a
> user story and implementation task. Therefore, we created 53 stories:
> 48 functional stories and 5 non-functional stories.
>
> Each story contains the requirement ID, description, priority, module label,
> story-point estimate, owner, sprint and test reference. This gives us
> requirement-to-code-to-test traceability.

### Example story explanation

> FR-34, “Top-5 leaderboard”, was assigned to Basavaraj. Its acceptance goal
> is that scores are sorted and only the best five are retained. The related
> implementation is `src/ScoreManager.cpp`, and the test is
> `test/test_score_manager.cpp`.

---

## 4. Sprints — 45 seconds

**Open:** GitHub → Issues → filter by **Milestone**.

| Sprint | Focus | Stories | Status |
|---|---|---:|---|
| Sprint-1 | First playable game: menus, grid, controls and basic game flow | 22 | 22 closed |
| Sprint-2 | Levels, obstacles, leaderboard, pause, game-over and quality goals | 31 | 31 closed |

> Sprint 1 focused on a basic playable game. Sprint 2 added the richer game
> features: persistent leaderboard, levels, obstacles, pause/resume and
> quality-related work. We used pull requests to merge completed work into the
> main branch.

---

## 5. How stories were assigned — 1 minute

**Open:** `docs/DEVELOPMENT.md` or GitHub Issues filtered by assignee.

> We assigned work based on the module ownership defined in our architecture
> document. Each member was given a complete functional area, rather than a
> random collection of small tasks.

| Member | Responsibility | Stories completed |
|---|---|---:|
| **Basava Prabhu** | Input, renderer, menus and screens | 16 / 16 |
| **Basavaraj Dhadake** | Game flow, pause/restart and score management | 13 / 13 |
| **Nikil Kumar Reddy** | Snake, food and collision modules | 12 / 12 |
| **Kodandapaani Reddy** | Levels, obstacles and performance requirements | 12 / 12 |

> GitHub records the assignee, branch, pull request and commits for these
> contributions. This makes individual contribution visible.

---

## 6. Individual contributions — 3 minutes

### Basava Prabhu — UI, controls and rendering

> I implemented the player-facing part of the game: main menu, difficulty
> selection, instructions, keyboard input, rendering of the grid, snake, food
> and obstacles, score/level/high-score HUD, pause overlay, level-up message,
> game-over screen, initials entry and leaderboard screen.

**Show:**

- `src/InputHandler.cpp`
- `src/Renderer.cpp`
- `src/screens/`

**Demo:** main menu → select difficulty → play → pause → game over → high scores.

### Basavaraj Dhadake — game flow and leaderboard

> I implemented score management and connected it to game flow. The game keeps
> the top five scores, saves them to `scores.dat`, loads them at startup,
> safely rejects corrupt score data and checks whether a player qualifies for
> the leaderboard. I also completed clean exit, reset, pause/resume and restart
> behavior.

**Show:**

- `src/ScoreManager.h` and `src/ScoreManager.cpp`
- `test/test_score_manager.cpp`

**Demo:** enter initials after a score → open leaderboard → restart the game →
show that scores remain available.

### Nikil Kumar Reddy — core game logic modules

> I created separate C++ modules for the snake, food and collision logic. The
> Snake module controls movement, direction validation and growth. The Food
> module places food only on valid empty cells. The CollisionDetector checks
> wall, self and obstacle collisions. I added standalone tests for all three
> modules.

**Show:**

- `src/Snake.cpp`, `src/Food.cpp`, `src/CollisionDetector.cpp`
- `tests/modules/test_snake.cpp`
- `tests/modules/test_food.cpp`
- `tests/modules/test_collision.cpp`

**Important, honest wording if asked about integration:**

> These modules are complete and tested independently. The existing playable
> application loop already contains the equivalent game behavior; the next
> cleanup step is to replace that temporary integrated logic with these
> dedicated modules everywhere in the application loop.

### Kodandapaani Reddy — levels, obstacles and performance

> I implemented difficulty-based tick speed, level progression up to level 10,
> obstacle creation, safe obstacle placement and the non-functional
> performance-related requirements.

**Show:**

- `include/LevelManager.hpp`, `src/LevelManager.cpp`
- `include/Obstacle.hpp`, `src/Obstacle.cpp`

**Demo:** start Easy/Medium/Hard → point out different speed/obstacle behavior
→ reach the level-up threshold → show increased speed and obstacles.

---

## 7. Testing and CI — 45 seconds

**Open:** GitHub → **Actions** and show the latest green run.

> We use GitHub Actions to build the project automatically on Ubuntu with SFML
> whenever code is pushed or a pull request is opened. This prevents broken code
> from being merged into the main branch.

### Evidence to show

- `test/test_grid.cpp` — grid and reset defaults
- `test/test_score_manager.cpp` — top five, saving/loading and corrupt-file handling
- `tests/modules/test_snake.cpp` — movement, direction and growth
- `tests/modules/test_food.cpp` — valid food placement
- `tests/modules/test_collision.cpp` — wall, self and obstacle collisions

> We do not claim that every quality requirement is perfectly benchmarked yet.
> We have implemented the quality safeguards and automated checks, while more
> detailed performance measurement can be extended in the final testing phase.

---

## 8. Live-demo order — 2 minutes

1. Launch the game.
2. Show the **main menu** and **difficulty selection**.
3. Start a game; show snake movement, food, score and HUD.
4. Show an obstacle/difficulty difference if available.
5. Press **P** to show pause; press **P** again to resume.
6. Trigger game over safely; show final score and restart/main-menu choices.
7. Enter initials for a qualifying score.
8. Open **High Scores** and show the leaderboard.
9. Optionally relaunch to demonstrate saved scores.

---

## 9. Likely questions and short answers

### How many user stories did you create?

> 53. We made one story for each of the 48 functional requirements and 5
> non-functional requirements in the SRS.

### How did you decide who gets which stories?

> We used the module ownership in our architecture/design document. UI went to
> Basava, score/game flow to Basavaraj, core snake/food/collision to Nikil, and
> levels/obstacles/performance to Kodandapaani.

### How many sprints did you have?

> Two. Sprint 1 had 22 stories and Sprint 2 had 31 stories. Both milestones are
> now complete in GitHub.

### How do you prove individual contribution?

> Each GitHub issue has an assignee. The repository also shows individual
> branches, pull requests, commits and module files for each contribution.

### How do you know the code works?

> The project builds through GitHub Actions, and we have unit tests for grid,
> score management, snake movement, food placement and collision detection.

### What remains after this review?

> The main remaining engineering cleanup is fully wiring the dedicated
> Snake/Food/Collision modules into the application loop, plus extending the
> formal test evidence and recording the required sprint videos.

---

## 10. Closing — 20 seconds

> In summary, we transformed our SRS into 53 traceable GitHub stories,
> organised them into two sprints and assigned them by module ownership. The
> result is a playable Snake Game with menus, difficulty modes, levels,
> obstacles, pause/resume, game-over flow and persistent high scores. GitHub
> Actions, pull requests and tests support our implementation process.

---

## Before the review: quick checklist

- [ ] Pull the newest `main` branch.
- [ ] Build and launch the game once before the review.
- [ ] Keep `SRS.docx`, GitHub Issues, GitHub Actions and the game open in tabs.
- [ ] Verify `scores.dat` behavior by entering a score and reopening the game.
- [ ] Make sure each member can explain their own files above.
- [ ] Do not claim a benchmark you cannot show; say “implemented, detailed measurement pending.”
- [ ] Record the required Sprint-1 and Sprint-2 videos if they have not been recorded.
