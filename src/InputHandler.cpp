#include "InputHandler.h"

namespace snake {

Command InputHandler::directionFromKey(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            return Command::Up;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            return Command::Down;
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            return Command::Left;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            return Command::Right;
        default:
            return Command::None;
    }
}

Command InputHandler::translateKey(sf::Keyboard::Key key) const {
    const Command dir = directionFromKey(key);
    if (dir != Command::None) {
        return dir;
    }

    switch (key) {
        case sf::Keyboard::P:
            return Command::Pause;
        case sf::Keyboard::R:
            return Command::Restart;
        case sf::Keyboard::M:
            return Command::Menu;
        case sf::Keyboard::Enter:
        case sf::Keyboard::Space:
            return Command::Confirm;
        case sf::Keyboard::Escape:
        case sf::Keyboard::BackSpace:
            return Command::Back;
        default:
            return Command::None;
    }
}

Command InputHandler::translate(const sf::Event& event) const {
    if (event.type != sf::Event::KeyPressed) {
        return Command::None;
    }
    return translateKey(event.key.code);
}

bool InputHandler::isDirection(Command command) {
    return command == Command::Up || command == Command::Down ||
           command == Command::Left || command == Command::Right;
}

} // namespace snake
