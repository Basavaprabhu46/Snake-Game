# Snake game logic modules

These standalone C++17 modules use the existing `snake::Cell` and
`snake::Command` types. They do not own application state, SFML objects,
obstacles, rendering, input events, or score persistence.

## Tick integration

For a game tick, the game engine can:

1. Ask `Snake::setDirection` to accept the latest direction command.
2. Use `Snake::nextHeadPosition()` to see the prospective head without moving.
   Determine whether that cell contains food, then call
   `CollisionDetector::checkTick(snake.body(), snake.direction(), obstacles,
   growing)` once. A collision result identifies `Wall`, `Self`, or `Obstacle`;
   the engine owns the Game Over transition.
3. If safe, call `Snake::move(growing)` exactly once.
4. On a food move, call `Food::consume(newHead, snake.body(), obstacles)`.
   The returned optional score delta is 10 when food was consumed. The caller
   adds that delta through its score owner.

The caller supplies obstacle positions as `std::vector<snake::Cell>`; these
modules do not depend on or modify `ObstacleManager`.

## Food exhaustion

`Food::respawn` returns `false` and clears its optional position if every grid
cell is occupied by the supplied snake or obstacles. An absent food position
means there is no legal cell available. The game engine decides how to present
that board state.

## Standalone tests

Configure and build only these modules and tests:

```sh
cmake -S tests/modules -B tests/modules/build
cmake --build tests/modules/build
ctest --test-dir tests/modules/build --output-on-failure
```
