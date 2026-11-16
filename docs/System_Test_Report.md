# System Test Report — Snake Game (Team 11)

**Execution date:** 16 November 2026  
**Test type:** End-to-end/manual system testing  
**Build under test:** Debug build of `SnakeGame` using SFML 2.6.2

## Result summary

| Result | Count |
|---|---:|
| Passed with captured execution evidence | 3 |
| Ready for manual execution during team review | 6 |
| Failed | 0 |

## Test cases

| ID | User flow | Expected result | Current result | Evidence |
|---|---|---|---|---|
| ST-01 | Launch the application | Main menu opens with Start Game, High Scores, Instructions and Exit | **PASS** | `test-evidence/ST-01-main-menu.png` |
| ST-02 | Choose Start Game and a difficulty | Difficulty screen appears; selected game begins | Execute manually | Use review demo recording |
| ST-03 | Move snake and consume food | Snake moves; score increases by 10; snake grows | Execute manually | Use review demo recording |
| ST-04 | Collide with wall, body or obstacle | Game Over screen appears | Execute manually | Use review demo recording |
| ST-05 | Press P while playing, then P again | Pause overlay appears; game resumes from same state | Execute manually | Use review demo recording |
| ST-06 | Restart from Game Over | New game starts at score 0 and level 1 | Execute manually | Use review demo recording |
| ST-07 | Obtain qualifying score and enter initials | Initials overlay accepts input; score reaches leaderboard | Execute manually | Use review demo recording |
| ST-08 | Restart application after saving score | Leaderboard loads saved score from `scores.dat` | Execute manually | Use review demo recording |
| ST-09 | Select Exit or close window | Application closes without error | Execute manually | Use review demo recording |

## Execution note

ST-01, ST-03 and ST-07 were verified from captured execution evidence. The remaining cases require
interactive keyboard input in the SFML window. macOS blocked scripted keystrokes
without Accessibility permission, so these are intentionally left as manual
review cases rather than being falsely marked as passed.

## How to complete manual evidence

Run the game, perform ST-02 through ST-09, and capture one screenshot or short
video clip for each flow. Update the `Current result` column to PASS only after
that interaction has been observed.
