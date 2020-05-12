#ifndef SAPER_BOARD_H
#define SAPER_BOARD_H

#include <vector>
#include "../config.h"
#include "Block.h"

class Board {
public:
    Board() = default;
    Board(unsigned int initWidth, unsigned int initHeight, unsigned int initBombsNumber);

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getBombsNumber() const;
    unsigned int getVisibleBlocksNumber();
    unsigned int getMarkedBlocks();
    Block getBlock(int row, int col);

    void revealBlock(int row, int col);
    bool remarkBlock(int row, int col);
    bool mapRevealed();
private:
    void initBoard ();
    void bombsPlanting ();
    void neighbouringGeneration();

    unsigned int width;
    unsigned int height;
    unsigned int visibleBlocksNumber;
    unsigned int bombsNumber;
    unsigned int markedBlocks;
    std::vector<std::vector<Block>> blocks;
};

#endif //SAPER_BOARD_H