#include "Visualizer.h"

Visualizer::Visualizer(Board &newBoard) {
    mainBoard = newBoard;
    menuOffset = INFO_HEIGHT;
    tileSize = Vector2u(IMG_SIZE, IMG_SIZE);
    width = tileSize.x * mainBoard.getWidth();
    height = tileSize.y * mainBoard.getHeight() + menuOffset;
}

unsigned int Visualizer::getWidth() const {
    return width;
}
unsigned int Visualizer::getHeight() const {
    return height;
}
unsigned int Visualizer::getUnmarkedBombs() {
    return mainBoard.getBombsNumber() - mainBoard.getMarkedBlocks();
}

bool Visualizer::showBombs() {
    for(int row = 0; row < mainBoard.getHeight(); row++) {
        for(int col = 0; col < mainBoard.getWidth(); col++) {
            if(mainBoard.getBlock(row,col).isBombed()) {
                mainBoard.revealBlock(row, col);
                reload(row,col);
            }
        }
    }
    return true;
}
bool Visualizer::showBlock(int row, int col) {
    if(row < 0 || row >= mainBoard.getHeight() || col < 0 || col >= mainBoard.getWidth() || mainBoard.getBlock(row,col).isVisible())
        return false;

    if(mainBoard.getBlock(row,col).isBombed())
        return showBombs();


    mainBoard.revealBlock(row,col);

    if(mainBoard.getBlock(row,col).getNeighbouringValue() == 0) {
        for(int i = row - 1; i <= row + 1; i++) {
            for(int j = col - 1; j <= col + 1; j++)
                showBlock(i, j);
        }
    }
    reload(row,col);
    return false;
}
void Visualizer::markBlock(int row, int col) {
    if(mainBoard.getBlock(row,col).isVisible())
        return;
    if(mainBoard.remarkBlock(row,col))
        reload(row,col);
}

bool Visualizer::mapRevealed() {
    return mainBoard.mapRevealed();
}

bool Visualizer::load() {
    
    if (!m_tileset.loadFromFile("Images/tileSet.png"))
        return false;

    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(width * height * 4);

    for (int i = 0; i < mainBoard.getWidth(); ++i) {
        for (int j = 0; j < mainBoard.getHeight(); ++j) {
            reload(j,i);
        }
    }
    return true;
}
unsigned int Visualizer::getTileNumber(int row, int col) {
    if (mainBoard.getBlock(row,col).isMarked())
        return 11;
    else if (!mainBoard.getBlock(row,col).isVisible())
        return 0;
    else if (mainBoard.getBlock(row,col).isBombed())
        return 10;
    
    return mainBoard.getBlock(row,col).getNeighbouringValue() + 1;
}
void Visualizer::reload(int row, int col) {    
    unsigned int tileNumber = getTileNumber(row,col);
    
    unsigned int tileX = tileNumber % (m_tileset.getSize().x / tileSize.x);

    /** get a pointer to the current tile's quad **/
    Vertex *quad = &m_vertices[(col + row * width) * 4];

    quad[0].position = Vector2f(col * tileSize.x, row * tileSize.y + menuOffset);
    quad[1].position = Vector2f((col + 1) * tileSize.x, row * tileSize.y + menuOffset);
    quad[2].position = Vector2f((col + 1) * tileSize.x, (row + 1) * tileSize.y + menuOffset);
    quad[3].position = Vector2f(col * tileSize.x, (row + 1) * tileSize.y + menuOffset);

    /** define its 4 texture coordinates **/
    quad[0].texCoords = Vector2f(tileX * tileSize.x, 0);
    quad[1].texCoords = Vector2f((tileX + 1) * tileSize.x, 0);
    quad[2].texCoords = Vector2f((tileX + 1) * tileSize.x,  tileSize.y);
    quad[3].texCoords = Vector2f(tileX * tileSize.x, tileSize.y);
}

void Visualizer::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &m_tileset;

    target.draw(m_vertices, states);
}