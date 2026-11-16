# Branch Coverage Report — Snake Game (Team 11)

**Execution date:** 16 November 2026  
**Tool:** Apple LLVM coverage (`llvm-profdata` + `llvm-cov`)  
**Build:** Debug instrumented build using `-fprofile-instr-generate -fcoverage-mapping`

## Result summary

| Production module | Branches covered | Branch coverage |
|---|---:|---:|
| `ScoreManager.cpp` | 27 / 42 | 64.29% |
| `Snake.cpp` | 49 / 54 | 90.74% |
| `Food.cpp` | 20 / 20 | 100.00% |
| `CollisionDetector.cpp` | 34 / 36 | 94.44% |
| `LevelManager.cpp` | 9 / 12 | 75.00% |
| `Obstacle.cpp` | 25 / 28 | 89.29% |
| **Overall (weighted)** | **164 / 192** | **85.42%** |

## Test inputs used

- Main project CTest suite: grid/reset and `ScoreManager` tests.
- Module CTest suite: Snake, Food and CollisionDetector tests.
- Assigned-issues executable: LevelManager, ObstacleManager and input-latency checks.

All six executed test programs passed.

## Reproduce locally

```bash
# Configure compiler coverage instrumentation.
cmake -S . -B build-coverage -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/sfml@2 \
  -DCMAKE_CXX_FLAGS='-fprofile-instr-generate -fcoverage-mapping' \
  -DCMAKE_EXE_LINKER_FLAGS='-fprofile-instr-generate -fcoverage-mapping'

# Run the test suites with LLVM_PROFILE_FILE set, merge .profraw files,
# then use xcrun llvm-cov report --show-branch-summary.
```

The detailed local HTML coverage output is generated under `coverage/html/` and is intentionally not versioned because it is a build artifact.
