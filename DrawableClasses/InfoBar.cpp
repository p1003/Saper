#include "InfoBar.h"

InfoBar::InfoBar(unsigned int initWidth, unsigned int initHeight, unsigned int bombs) {
    width = IMG_SIZE * initWidth;
    height = initHeight;
    bombsLeft = bombs;
    timer = 0;
    tileSize = Vector2u(SM_IMG_SIZE, IMG_SIZE);
    initOffsets();
}
void InfoBar::initOffsets() {
    unsigned int breakOffset = (width - 8 * SM_IMG_SIZE - IMG_SIZE) / 2;
    for(int i = 0; i < 5; i++) {
        iconOffsets.push_back(i * SM_IMG_SIZE);
    }
    iconOffsets.push_back(4 * SM_IMG_SIZE + breakOffset);
    for(int i = 5; i < 8; i++) {
        iconOffsets.push_back(2 * breakOffset + IMG_SIZE + i * SM_IMG_SIZE);
    }
}

void InfoBar::timeUpdate(int actual) {
    if(timer < actual) {
        loadQuad(4, actual % 10, tileSize.x);
        if(timer / 10 != actual / 10)
            loadQuad(3, (actual % 60) / 10, tileSize.x);
        if(timer / 60 != actual / 60)
            loadQuad(1, ((actual) / 60) % 10, tileSize.x);
        if(timer / 600 != actual / 600)
            loadQuad(0, ((actual) / 600) % 10, tileSize.x);
        timer = actual;
    }
}
void InfoBar::bombUpdate(unsigned int actual) {
    if(bombsLeft != actual) {
        loadQuad(8, actual % 10, tileSize.x);
        if(bombsLeft / 10 != actual / 10)
            loadQuad(7, (actual / 10) % 10, tileSize.x);
        if(bombsLeft / 100 != actual / 100)
            loadQuad(6, (actual / 100) % 10, tileSize.x);
        bombsLeft = actual;
    }
}
void InfoBar::faceUpdate() {
    unsigned int tileX = 13;
    unsigned int tileSizeX = IMG_SIZE;
    loadQuad(5,tileX,tileSizeX);
}

bool InfoBar::restartRequest(unsigned int mouseX) {
    return mouseX > iconOffsets[5] && mouseX <= iconOffsets[5] + IMG_SIZE;
}

bool InfoBar::load() {
    if (!m_tileset.loadFromFile("Images/infoSet.png"))
        return false;

    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(4 * 9);

    for (int i = 0; i < 6; ++i)
        initLoader(i);
    unsigned int actual = bombsLeft;
    bombsLeft = 0;
    bombUpdate(actual);

    return true;
}
void InfoBar::initLoader(int index) {

    unsigned int tileX;
    if(index == 2) {
        tileX = 10;
    }
    else if(index == 5) {
        tileX = 11;
    }
    else
        tileX = 0;

    unsigned int tileSizeX;
    if(index != 5)
        tileSizeX = tileSize.x;
    else
        tileSizeX = IMG_SIZE;
    loadQuad(index, tileX, tileSizeX);
}
void InfoBar::loadQuad (int index, unsigned int tileX, unsigned int tileSizeX) {
    Vertex *quad = &m_vertices[index * 4];

    quad[0].position = Vector2f(iconOffsets[index], 0);
    quad[1].position = Vector2f(iconOffsets[index] + tileSizeX, 0);
    quad[2].position = Vector2f(iconOffsets[index] + tileSizeX, tileSize.y);
    quad[3].position = Vector2f(iconOffsets[index], tileSize.y);

    /** define its 4 texture coordinates **/
    quad[0].texCoords = Vector2f(tileX * tileSize.x, 0);
    quad[1].texCoords = Vector2f(tileX * tileSize.x + tileSizeX, 0);
    quad[2].texCoords = Vector2f(tileX * tileSize.x + tileSizeX, tileSize.y);
    quad[3].texCoords = Vector2f(tileX * tileSize.x, tileSize.y);
}

void InfoBar::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &m_tileset;

    target.draw(m_vertices, states);
}