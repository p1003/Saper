#include "Menu.h"

Menu::Menu(unsigned int initWidth, unsigned int initHeight) {
    width = initWidth;
    height = initHeight;
    tileSize = Vector2u(IMG_SIZE, IMG_SIZE);
    setInit(diffLevel::EASY);
    initOffsets();
}
void Menu::initOffsets() {
    unsigned int offset = 0;
    for(int i = 0; i < 13; i++) {
        if(i == 4 || i == 8)
            offset += IMG_SIZE;
        iconOffsets.push_back(offset + i * SM_IMG_SIZE);
    }
}
void Menu::setInit(diffLevel level) {
    initializer.initWidth = WIDTHS[level];
    initializer.initHeight = HEIGHTS[level];
    initializer.initBombs = BOMBS[level];
}

initValues Menu::getInitializer() {
    return initializer;
}

bool Menu::start(unsigned int mouseX) {
    if(mouseX >= tileSize.x * 4)
        return false;
    if(mouseX < tileSize.x)
        setInit(diffLevel::EASY);
    else if(mouseX < tileSize.x * 2)
        setInit(diffLevel::MEDIUM);
    else if(mouseX < tileSize.x * 3)
        setInit(diffLevel::HARD);
    return true;
}

unsigned int getNumber (unsigned int value, unsigned int pos) {
    switch (pos) {
        case 0:
            return value % 10 + 8;
        case 1:
            return (value / 10) % 10 + 8;
        case 2:
            return (value / 100) % 10 + 8;
        default:
            return 1;
    }
}
void Menu::changeSandboxValue(unsigned int mouseX, unsigned int mouseY) {
    if(mouseY >= SM_IMG_SIZE * 4 + 2 * FONT_SIZE + 4 * FONT_OFFSET && mouseY < SM_IMG_SIZE * 5 + 2 * FONT_SIZE + 4 * FONT_OFFSET) {
        if(mouseX >= SM_IMG_SIZE * 3 && mouseX < SM_IMG_SIZE * 4 && initializer.initWidth > MIN_WIDTH) {
            initializer.initWidth--;
            updateSandboxValue(0);
        }
        else if(mouseX >= SM_IMG_SIZE * 9 && mouseX < SM_IMG_SIZE * 10 && initializer.initHeight > MIN_HEIGHT) {
            initializer.initHeight--;
            updateSandboxValue(1);
        }
        else if(mouseX >= SM_IMG_SIZE * 16 && mouseX < SM_IMG_SIZE * 17 && initializer.initBombs > 1) {
            initializer.initBombs--;
            updateSandboxValue(2);
        }
    }
    else if (mouseY >= SM_IMG_SIZE * 3 + 2 * FONT_SIZE + 4 * FONT_OFFSET && mouseY < SM_IMG_SIZE * 4 + 2 * FONT_SIZE + 4 * FONT_OFFSET){
        if(mouseX >= SM_IMG_SIZE * 3 && mouseX < SM_IMG_SIZE * 4 && initializer.initWidth < MAX_WIDTH) {
            initializer.initWidth++;
            updateSandboxValue(0);
        }
        else if(mouseX >= SM_IMG_SIZE * 9 && mouseX < SM_IMG_SIZE * 10 && initializer.initHeight < MAX_HEIGHT) {
            initializer.initHeight++;
            updateSandboxValue(1);
        }
        else if(mouseX >= SM_IMG_SIZE * 16 && mouseX < SM_IMG_SIZE * 17 && initializer.initBombs < initializer.initWidth * initializer.initHeight) {
            initializer.initBombs++;
            updateSandboxValue(2);
        }
    }
}
void Menu::updateSandboxValue(int type) {
    switch (type) {
        case 0:
            for(int i = 1; i <= 2; i++) {
                unsigned int tileX = getNumber(initializer.initWidth,2 - i);
                loadQuad(i+4, SM_IMG_SIZE * 3 + 2 * FONT_SIZE + 4 * FONT_OFFSET, iconOffsets[i], tileX, SM_IMG_SIZE);
            }
            break;
        case 1:
            for(int i = 1; i <= 2; i++) {
                unsigned int tileX = getNumber(initializer.initHeight,2 - i);
                loadQuad(i+8, SM_IMG_SIZE * 3 + 2 * FONT_SIZE + 4 * FONT_OFFSET, iconOffsets[i + 4], tileX, SM_IMG_SIZE);
            }
            break;
        case 2:
            for(int i = 1; i <= 3; i++) {
                unsigned int tileX = getNumber(initializer.initBombs,3 - i);
                loadQuad(i+12, SM_IMG_SIZE * 3 + 2 * FONT_SIZE + 4 * FONT_OFFSET, iconOffsets[i + 8], tileX, SM_IMG_SIZE);
            }
            break;
        default:
            break;
    }
}

bool Menu::load() {
    if (!m_tileset.loadFromFile("Images/menuSet.png"))
        return false;

    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(4 * 17);

    loadMenu();
    loadSandboxValues();

    return true;
}
void Menu::loadMenu() {
    for(int i = 0; i < 4; i++)
        loadQuad(i,FONT_SIZE + 2 * FONT_OFFSET,i*tileSize.x,i,tileSize.x);
}
void Menu::loadSandboxValues() {
    for(int i = 0; i < 13; i++) {
        unsigned int tileX = -1;
        if(i == 3 || i == 7 || i == 12)
            tileX = 18;
        else if(i==0)
            tileX = 19;
        else if(i==4)
            tileX = 20;
        else if(i==8)
            tileX = 21;
        if(tileX != -1)
            loadQuad(i+4, IMG_SIZE + SM_IMG_SIZE + 2 * FONT_SIZE + 4 * FONT_OFFSET, iconOffsets[i], tileX, SM_IMG_SIZE);
    }
    updateSandboxValue(0);
    updateSandboxValue(1);
    updateSandboxValue(2);
}
void Menu::loadQuad(int index, unsigned int posY, unsigned int posX, unsigned int tileX, unsigned int tileSizeX) {
    Vertex *quad = &m_vertices[index * 4];

    quad[0].position = Vector2f(posX, posY);
    quad[1].position = Vector2f(posX + tileSizeX, posY);
    quad[2].position = Vector2f(posX + tileSizeX, tileSize.y + posY);
    quad[3].position = Vector2f(posX, tileSize.y + posY);

    quad[0].texCoords = Vector2f(tileX * tileSizeX, 0);
    quad[1].texCoords = Vector2f((tileX + 1) * tileSizeX, 0);
    quad[2].texCoords = Vector2f((tileX + 1) * tileSizeX, tileSize.y);
    quad[3].texCoords = Vector2f(tileX * tileSizeX, tileSize.y);
}

void Menu::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &m_tileset;

    target.draw(m_vertices, states);
}