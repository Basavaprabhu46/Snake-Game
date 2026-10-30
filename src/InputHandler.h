#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Types.h"

namespace snake {

// ---------------------------------------------------------------------------
// InputHandler  (FR-02, FR-09, FR-44)
//
// Translates raw SFML input into game-independent Commands. It performs NO
// game-state checks (e.g. ignoring direction while paused is the GameEngine's
// responsibility), keeping this class pure and easy to unit test.
// ---------------------------------------------------------------------------
class InputHandler {
public:
    // Translate a single SFML event. Returns Command::None for events that do
    // not map to a command (mouse move, resize, etc.).
    Command translate(const sf::Event& event) const;

    // Translate a pressed key. Useful for held-key movement polling.
    Command translateKey(sf::Keyboard::Key key) const;

    // True for Up/Down/Left/Right.
    static bool isDirection(Command command);

private:
    // Main-menu navigation and gameplay share the arrow/WASD keys; the caller
    // decides what a direction means in the current screen.
    static Command directionFromKey(sf::Keyboard::Key key);
};

} // namespace snake
