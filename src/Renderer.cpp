#include "Renderer.h"
#include "HudText.h"

#include <array>
#include <string>
#include <vector>

namespace snake {

// Colours (kept together so the palette is easy to tweak).
namespace {
const sf::Color kBoardBg(24, 28, 34);
const sf::Color kGridLine(35, 40, 48);
const sf::Color kBoardBorder(60, 66, 78);
const sf::Color kHudBg(28, 34, 42);
const sf::Color kSnakeHead(90, 225, 130);
const sf::Color kSnakeBody(52, 170, 92);
const sf::Color kFood(232, 72, 72);
const sf::Color kObstacle(110, 110, 126);
const sf::Color kObstacleEdge(70, 70, 84);
const sf::Color kText(232, 238, 245);
const sf::Color kAccent(250, 210, 70);
const sf::Color kDanger(240, 90, 90);
} // namespace

Renderer::Renderer(sf::RenderWindow& window) : window_(window) {}

bool Renderer::loadFont() {
    std::vector<std::string> candidates;
#ifdef SNAKE_ASSETS_DIR
    candidates.push_back(std::string(SNAKE_ASSETS_DIR) +
                         "/fonts/PressStart2P-Regular.ttf");
#endif
    candidates.push_back("assets/fonts/PressStart2P-Regular.ttf");
    candidates.push_back("../assets/fonts/PressStart2P-Regular.ttf");
    candidates.push_back("/System/Library/Fonts/Supplemental/Arial.ttf");
    candidates.push_back("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    for (const auto& path : candidates) {
        if (font_.loadFromFile(path)) {
            fontLoaded_ = true;
            return true;
        }
    }
    fontLoaded_ = false;
    return false;
}

sf::Vector2f Renderer::cellToPixel(int col, int row) const {
    return sf::Vector2f(static_cast<float>(MARGIN + col * CELL_SIZE),
                        static_cast<float>(HUD_HEIGHT + row * CELL_SIZE));
}

// ---------------------------------------------------------------------------
// Generic helpers
// ---------------------------------------------------------------------------
void Renderer::drawRect(float x, float y, float w, float h, sf::Color fill) {
    sf::RectangleShape rect(sf::Vector2f(w, h));
    rect.setPosition(x, y);
    rect.setFillColor(fill);
    window_.draw(rect);
}

void Renderer::drawRectOutline(float x, float y, float w, float h,
                               float thickness, sf::Color color) {
    sf::RectangleShape rect(sf::Vector2f(w, h));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(thickness);
    rect.setOutlineColor(color);
    window_.draw(rect);
}

void Renderer::drawOverlay(sf::Color tint) {
    drawRect(0.f, 0.f, static_cast<float>(windowWidth()),
             static_cast<float>(windowHeight()), tint);
}

void Renderer::drawText(const std::string& text, unsigned size, float x, float y,
                        sf::Color color, bool centerHorizontally) {
    if (!fontLoaded_) {
        return;
    }
    sf::Text label;
    label.setFont(font_);
    label.setString(text);
    label.setCharacterSize(size);
    label.setFillColor(color);

    if (centerHorizontally) {
        const sf::FloatRect bounds = label.getLocalBounds();
        label.setPosition(x - bounds.left - bounds.width / 2.f, y);
    } else {
        label.setPosition(x, y);
    }
    window_.draw(label);
}

void Renderer::drawTextCentered(const std::string& text, unsigned size,
                                float centerY, sf::Color color) {
    if (!fontLoaded_) {
        return;
    }
    sf::Text label;
    label.setFont(font_);
    label.setString(text);
    label.setCharacterSize(size);
    label.setFillColor(color);

    const sf::FloatRect bounds = label.getLocalBounds();
    label.setPosition(static_cast<float>(windowWidth()) / 2.f - bounds.left -
                          bounds.width / 2.f,
                      centerY - bounds.top - bounds.height / 2.f);
    window_.draw(label);
}

// ---------------------------------------------------------------------------
// Game world
// ---------------------------------------------------------------------------
void Renderer::drawGrid() {
    const float boardX = static_cast<float>(MARGIN);
    const float boardY = static_cast<float>(HUD_HEIGHT);
    const float boardW = static_cast<float>(GRID_COLS * CELL_SIZE);
    const float boardH = static_cast<float>(GRID_ROWS * CELL_SIZE);

    drawRect(boardX, boardY, boardW, boardH, kBoardBg);

    for (int col = 0; col <= GRID_COLS; ++col) {
        const float x = boardX + static_cast<float>(col * CELL_SIZE);
        drawRect(x, boardY, 1.f, boardH, kGridLine);
    }
    for (int row = 0; row <= GRID_ROWS; ++row) {
        const float y = boardY + static_cast<float>(row * CELL_SIZE);
        drawRect(boardX, y, boardW, 1.f, kGridLine);
    }
    drawRectOutline(boardX, boardY, boardW, boardH, 2.f, kBoardBorder);
}

void Renderer::drawSnake(const RenderData& data) {
    for (std::size_t i = 0; i < data.snake.size(); ++i) {
        const Cell& cell = data.snake[i];
        const sf::Vector2f p = cellToPixel(cell.x, cell.y);
        const sf::Color color = (i == 0) ? kSnakeHead : kSnakeBody;
        drawRect(p.x + 2.f, p.y + 2.f, CELL_SIZE - 4.f, CELL_SIZE - 4.f, color);
    }
}

void Renderer::drawFood(const RenderData& data) {
    if (data.food.x < 0) {
        return;
    }
    const sf::Vector2f p = cellToPixel(data.food.x, data.food.y);
    sf::CircleShape food(CELL_SIZE / 2.f - 5.f);
    food.setFillColor(kFood);
    food.setPosition(p.x + 5.f, p.y + 5.f);
    window_.draw(food);
}

void Renderer::drawObstacles(const RenderData& data) {
    for (const Cell& cell : data.obstacles) {
        const sf::Vector2f p = cellToPixel(cell.x, cell.y);
        drawRect(p.x + 2.f, p.y + 2.f, CELL_SIZE - 4.f, CELL_SIZE - 4.f,
                 kObstacle);
        drawRectOutline(p.x + 2.f, p.y + 2.f, CELL_SIZE - 4.f, CELL_SIZE - 4.f,
                        2.f, kObstacleEdge);
    }
}

void Renderer::drawHUD(const RenderData& data) {
    drawRect(0.f, 0.f, static_cast<float>(windowWidth()),
             static_cast<float>(HUD_HEIGHT), kHudBg);
    drawRect(0.f, static_cast<float>(HUD_HEIGHT) - 2.f,
             static_cast<float>(windowWidth()), 2.f, kBoardBorder);

    const float top = 14.f;
    drawText("SCORE " + std::to_string(data.score), 13, 4.0f + MARGIN, top,
             kText);
    drawText("LEVEL " + std::to_string(data.level), 13,
             static_cast<float>(windowWidth()) / 2.f, top, kAccent, true);
  drawText(highScoreLabel(data), 13,
         static_cast<float>(windowWidth()) - MARGIN, top, kText, true);
}

void Renderer::drawGame(const RenderData& data) {
    drawGrid();
    drawObstacles(data);
    drawFood(data);
    drawSnake(data);
    drawHUD(data);
    if (data.showLevelUp) {
        drawLevelUpBanner();
    }
}

void Renderer::drawPausedOverlay() {
    drawOverlay(sf::Color(0, 0, 0, 160));
    drawTextCentered("PAUSED", 30,
                     static_cast<float>(HUD_HEIGHT + GRID_ROWS * CELL_SIZE / 2),
                     kAccent);
    drawTextCentered("Press P to Resume", 13,
                     static_cast<float>(HUD_HEIGHT + GRID_ROWS * CELL_SIZE / 2 +
                                        50),
                     kText);
}

void Renderer::drawLevelUpBanner() {
    drawTextCentered("LEVEL UP!", 26,
                     static_cast<float>(HUD_HEIGHT + GRID_ROWS * CELL_SIZE / 2),
                     kAccent);
}

void Renderer::drawGameOver(const RenderData& data) {
    drawOverlay(sf::Color(0, 0, 0, 190));
    drawTextCentered("GAME OVER", 32, 180.f, kDanger);
    drawTextCentered("Score: " + std::to_string(data.score), 16, 250.f, kText);
    drawTextCentered("Level: " + std::to_string(data.level), 16, 285.f, kText);
    drawTextCentered("[R] Restart    [M] Main Menu", 13, 360.f, kAccent);
}

void Renderer::drawScoreEntry(const std::string& initials, int score) {
    drawOverlay(sf::Color(0, 0, 0, 190));
    drawTextCentered("NEW HIGH SCORE!", 22, 160.f, kAccent);
    drawTextCentered("Score: " + std::to_string(score), 16, 215.f, kText);
    drawTextCentered("Enter initials:", 13, 280.f, kText);

    std::string shown = initials;
    shown += "_";
    drawTextCentered(shown, 26, 330.f, kSnakeHead);

    drawTextCentered("[Enter] Confirm   [Backspace] Delete", 11, 400.f, kText);
}

} // namespace snake
