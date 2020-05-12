#ifndef SAPER_BLOCK_H
#define SAPER_BLOCK_H

class Block {
public:
    Block();

    bool isVisible();
    bool isBombed();
    bool isMarked();
    unsigned int getNeighbouringValue();

    void placeBomb();
    void reveal();
    void remark();
    void setNeighbouringValue(unsigned int value);
private:
    bool visible;
    bool bombed;
    bool marked;
    unsigned int neighbouringValue;
};

#endif //SAPER_BLOCK_H
