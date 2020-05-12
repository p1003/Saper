#include "Block.h"

Block::Block() {
    visible = false;
    bombed = false;
    marked = false;
    neighbouringValue = 0;
}

bool Block::isVisible() {
    return visible;
}
bool Block::isBombed() {
    return bombed;
}
bool Block::isMarked() {
    return marked;
}
unsigned int Block::getNeighbouringValue() {
    return neighbouringValue;
}

void Block::placeBomb() {
    bombed = true;
}
void Block::reveal() {
    visible = true;
}
void Block::remark() {
    marked = !marked;
}
void Block::setNeighbouringValue(unsigned int value) {
    neighbouringValue = value;
}