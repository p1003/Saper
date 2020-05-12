#ifndef SAPER_CONFIG_H
#define SAPER_CONFIG_H

#define IMG_SIZE 30
#define SM_IMG_SIZE 15
#define INFO_HEIGHT 30
#define MIN_WIDTH 8
#define MAX_WIDTH 50
#define MIN_HEIGHT 5
#define MAX_HEIGHT 32
#define MENU_WIDTH 300
#define MENU_HEIGHT 130
#define FONT_SIZE 19
#define FONT_OFFSET 3

typedef enum diffLevel {
    EASY = 0, MEDIUM = 1, HARD = 2
} diffLevel;

struct initValues {
    unsigned int initWidth;
    unsigned int initHeight;
    unsigned int initBombs;
};

const static int WIDTHS[] = {8, 16, 32};
const static int HEIGHTS[] = {8, 16, 32};
const static int BOMBS[] = {10, 46, 205};

#endif //SAPER_CONFIG_H
