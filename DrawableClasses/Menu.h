#ifndef SAPER_MENU_H
#define SAPER_MENU_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../config.h"

using namespace sf;

class Menu : public Drawable, public Transformable {
public:
    Menu(unsigned int initWidth, unsigned int initHeight);

    initValues getInitializer();

    bool start(unsigned int mouseX);
    void changeSandboxValue(unsigned int mouseX, unsigned int mouseY);

    bool load();
private:
    void initOffsets();
    void setInit (diffLevel value);

    void updateSandboxValue(int type);

    void loadMenu();
    void loadSandboxValues();
    void loadQuad(int index, unsigned int posY, unsigned int posX, unsigned int tileX, unsigned int tileSizeX);

    virtual void draw(RenderTarget &target, RenderStates states) const;

    unsigned int width;
    unsigned int height;
    initValues initializer;
    Vector2u tileSize;
    VertexArray m_vertices;
    Texture m_tileset;
    std::vector<unsigned int> iconOffsets;
};

#endif //SAPER_MENU_H