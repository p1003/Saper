#ifndef SAPER_SAPERGAME_H
#define SAPER_SAPERGAME_H

#include "../SFML/include/SFML/Graphics.hpp"
#include "../SFML/include/SFML/Window.hpp"

#include "../config.h"
#include "../GameClasses/Board.h"
#include "../DrawableClasses/Visualizer.h"
#include "../DrawableClasses/InfoBar.h"
#include "../DrawableClasses/Menu.h"

class SaperGame {
public:
    SaperGame();
    void startGame();
private:
    bool gameLost;
    bool gameRestart;
    bool gameStarted;
    bool gameExit;
    initValues initializer;

    void menuEventHandler(RenderWindow &menuWindow, Menu &mainMenu, Event event);
    void gameEventHandler(RenderWindow &gameWindow, Visualizer &visualizer, InfoBar &infoBar, Event event);
};


#endif //SAPER_SAPERGAME_H
