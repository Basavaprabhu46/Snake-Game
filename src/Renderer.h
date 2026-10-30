#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Types.h"

namespace snake {

// ---------------------------------------------------------------------------
// Renderer  (FR-12, FR-17, FR-26, FR-27, FR-32, FR-39, FR-42)
//
// Draws the game grid, snake, food, obstacles, HUD and overlays using SFML.
// It consumes a data-only RenderData snapshot so the presentation layer never
// reaches into game-logic classes. Also exposes small draw helpers reused by
// the menu / game-over / high-score screens.
// ---------------------------------------------------------------------------
class Renderer {
public:
    static constexpr int CELL_SIZE = 28;
    static constexpr int MARGIN = 20;
    static constexpr int HUD_HEIGHT = 80;
    static constexpr int GRID_COLS = 20;
    static constexpr int GRID_ROWS = 20;

    static unsigned windowWidth() {
        return static_cast<unsigned>(GRID_COLS * CELL_SIZE + 2 * MARGIN);
    }
    static unsigned windowHeight() {
        return static_cast<unsigned>(HUD_HEIGHT + GRID_ROWS * CELL_SIZE + MARGIN);
    }

    explicit Renderer(sf::RenderWindow& window);

    // Attempts to load the bundled font. Safe to call once at startup.
    bool loadFont();
    bool hasFont() const { return fontLoaded_; }

    // --- Game world -------------------------------------------------------
    void drawGame(const RenderData& data);   // grid + entities + HUD
    void drawHUD(const RenderData& data);    // score / level / high score
    void drawPausedOverlay();                // FR-42
    void drawLevelUpBanner();                // FR-27
    void drawGameOver(const RenderData& data); // FR-45 presentation

    // --- Generic helpers (used by the screen classes) ---------------------
    void drawOverlay(sf::Color tint);        // full-window translucent tint
    void drawRect(float x, float y, float w, float h, sf::Color fill);
    void drawRectOutline(float x, float y, float w, float h, float thickness,
                         sf::Color color);
    void drawText(const std::string& text, unsigned size, float x, float y,
                  sf::Color color, bool centerHorizontally = false);
    void drawTextCentered(const std::string& text, unsigned size, float centerY,
                          sf::Color color);
    void drawScoreEntry(const std::string& initials, int score);

    sf::Vector2f cellToPixel(int col, int row) const;

private:
    void drawGrid();
    void drawSnake(const RenderData& data);
    void drawFood(const RenderData& data);
    void drawObstacles(const RenderData& data);

    sf::RenderWindow& window_;
    sf::Font font_;
    bool fontLoaded_ = false;
};

} // namespace snake
