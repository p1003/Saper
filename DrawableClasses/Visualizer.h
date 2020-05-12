#ifndef SAPER_VISUALIZER_H
#define SAPER_VISUALIZER_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../config.h"
#include "../GameClasses/Board.h"

using namespace sf;

class Visualizer : public Drawable, public Transformable {
public:
    explicit Visualizer(Board &newBoard);

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getUnmarkedBombs();

    bool showBombs();
    bool showBlock(int row, int col);
    void markBlock(int row, int col);

    bool mapRevealed();

    bool load();
    unsigned int getTileNumber(int row, int col);
    void reload(int row, int col);
private:
    virtual void draw(RenderTarget &target, RenderStates states) const;

    unsigned int width;
    unsigned int height;
    unsigned int menuOffset;
    Board mainBoard;
    Vector2u tileSize;
    VertexArray m_vertices;
    Texture m_tileset;
};

#endif //SAPER_VISUALIZER_H