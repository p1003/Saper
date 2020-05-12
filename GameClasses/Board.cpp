#include <iostream>
#include <random>
#include <ctime>

#include "Board.h"

using namespace std;

Board::Board(unsigned int initWidth, unsigned int initHeight, unsigned int initBombsNumber) {
    width = initWidth;
    height = initHeight;
    visibleBlocksNumber = 0;
    bombsNumber = initBombsNumber;
    markedBlocks = 0;

    initBoard();
    bombsPlanting();
    neighbouringGeneration();
}

void Board::initBoard() {
    if(!blocks.empty()) {
        for(auto iterator : blocks)
            iterator.clear();
        blocks.clear();
    }
    for(int row = 0; row < height; row++) {
        vector<Block> visibleRow (width);
        blocks.push_back(visibleRow);
    }
}
void Board::bombsPlanting() {

    if(bombsNumber > width * height - 1) {
        bombsNumber = width * height - 1;
        cout << "Too high number of bombs provided. Their number set as " << width * height - 1 << endl;
    }
    
    /** placing bombs on the field
        bombed cell has value of 9 **/

    int bombsPlaced = 0;
    random_device rd;
    mt19937 gen((unsigned int)time(nullptr));
    std::uniform_int_distribution<> disRow(0, height - 1);
    std::uniform_int_distribution<> disCol(0, width - 1);
    while(bombsPlaced < bombsNumber) {
        int row = disRow(gen);
        int col = disCol(gen);
        if(!blocks[row][col].isBombed()) {
            blocks[row][col].placeBomb();
            bombsPlaced++;
        }
    }
}
void Board::neighbouringGeneration() {
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            if(!blocks[row][col].isBombed()) {
                int neighBombs = 0;
                for(int rowIter = row - 1; rowIter <= row + 1; rowIter++) {
                    if(rowIter < 0) rowIter++;
                    if(rowIter >= height) break;
                    for(int colIter = col - 1; colIter <= col + 1; colIter++) {
                        if(colIter < 0) colIter++;
                        if(colIter >= width) break;
                        if(blocks[rowIter][colIter].isBombed())
                            neighBombs++;
                    }
                }
                blocks[row][col].setNeighbouringValue(neighBombs);
            }
        }
    }
}

unsigned int Board::getWidth() const {
    return width;
}
unsigned int Board::getHeight() const {
    return height;
}
unsigned int Board::getBombsNumber() const {
    return bombsNumber;
}
unsigned int Board::getVisibleBlocksNumber() {
    return visibleBlocksNumber;
}
unsigned int Board::getMarkedBlocks() {
    return markedBlocks;
}
Block Board::getBlock(int row, int col) {
    if(row < 0 || row > height || col < 0 || col > width)
        throw invalid_argument("Out of range");
    return blocks[row][col];
}

void Board::revealBlock(int row, int col) {
    blocks[row][col].reveal();
    if(!blocks[row][col].isBombed())
        visibleBlocksNumber++;
}
bool Board::remarkBlock(int row, int col) {
    if(!blocks[row][col].isMarked()) {
        if(markedBlocks < bombsNumber) {
            blocks[row][col].remark();
            markedBlocks++;
            return true;
        }
        return false;
    }
    blocks[row][col].remark();
    markedBlocks--;
    return true;
}
bool Board::mapRevealed() {
    return width * height - visibleBlocksNumber - markedBlocks <= 0;
}