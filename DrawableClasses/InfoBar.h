#ifndef SAPER_INFOBAR_H
#define SAPER_INFOBAR_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../config.h"

using namespace sf;

class InfoBar : public Drawable, public Transformable {
public:
    InfoBar(unsigned int initWidth, unsigned int initHeight, unsigned int bombs);

    void timeUpdate(int actual);
    void bombUpdate(unsigned int actual);
    void faceUpdate();

    bool restartRequest(unsigned int mouseX);

    bool load();
private:
    void initOffsets();
    void loadQuad(int index, unsigned int tileX, unsigned int tileSizeX);
    virtual void draw(RenderTarget &target, RenderStates states) const;
    void initLoader(int index);

    unsigned int width;
    unsigned int height;
    unsigned int bombsLeft;
    int timer;

    Vector2u tileSize;
    VertexArray m_vertices;
    Texture m_tileset;
    std::vector<unsigned int> iconOffsets;
};


#endif //SAPER_INFOBAR_H
