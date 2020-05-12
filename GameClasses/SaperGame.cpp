#include "SaperGame.h"

SaperGame::SaperGame() {
    gameExit = false;
    gameLost = false;
    gameStarted = false;
    gameRestart = false;
}

void SaperGame::menuEventHandler(RenderWindow &menuWindow, Menu &mainMenu, Event event) {
    switch (event.type) {
        case Event::Closed:
            gameExit = true;
            menuWindow.close();
            break;
        case Event::MouseButtonPressed:
            if(event.mouseButton.button == Mouse::Left) {
                if(event.mouseButton.y < INFO_HEIGHT + FONT_SIZE + 2 * FONT_OFFSET && event.mouseButton.y >= FONT_SIZE + 2 * FONT_OFFSET)
                    gameStarted = mainMenu.start(event.mouseButton.x);
                else
                    mainMenu.changeSandboxValue(event.mouseButton.x,event.mouseButton.y);
            }
            break;
        default:
            break;
    }
}

void SaperGame::gameEventHandler(RenderWindow &gameWindow, Visualizer &visualizer, InfoBar &infoBar, Event event) {
    switch (event.type) {
        case Event::Closed:
            gameStarted = false;
            gameWindow.close();
            break;
        case Event::MouseButtonPressed:
            switch (event.mouseButton.button) {
                case Mouse::Left:
                    if(event.mouseButton.y < INFO_HEIGHT)
                        gameRestart = infoBar.restartRequest(event.mouseButton.x);
                    else if(!gameLost) {
                        if(!gameStarted)
                            gameStarted = true;
                        gameLost = visualizer.showBlock((event.mouseButton.y - INFO_HEIGHT) / IMG_SIZE, event.mouseButton.x / IMG_SIZE);
                        if(gameLost)
                            infoBar.faceUpdate();
                    }
                    break;
                case Mouse::Right:
                    if(!gameLost && event.mouseButton.y >= INFO_HEIGHT) {
                        if(!gameStarted)
                            gameStarted = true;
                        visualizer.markBlock((event.mouseButton.y - INFO_HEIGHT) / IMG_SIZE,
                                             event.mouseButton.x / IMG_SIZE);
                        infoBar.bombUpdate(visualizer.getUnmarkedBombs());
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void SaperGame::startGame() {
    do {
        if(!gameRestart) {
            RenderWindow starterWindow(VideoMode(MENU_WIDTH,MENU_HEIGHT),"Menu",Style::Close | Style::Titlebar);
            starterWindow.setVerticalSyncEnabled(true);

            Menu mainMenu(MENU_WIDTH,MENU_HEIGHT);
            if (!mainMenu.load())
                return;

            Font font;
            if(!font.loadFromFile("fonts/8bitOperatorPlus-Bold.ttf"))
                return;
            Text difficultyLevels;
            difficultyLevels.setFont(font);
            difficultyLevels.setString("Choose difficulty");
            difficultyLevels.setCharacterSize(FONT_SIZE-1);
            difficultyLevels.setFillColor(Color::White);
            difficultyLevels.setPosition(FONT_OFFSET,FONT_OFFSET);

            Text sandboxValues;
            sandboxValues.setFont(font);
            sandboxValues.setString("Sandbox values");
            sandboxValues.setCharacterSize(FONT_SIZE-1);
            sandboxValues.setFillColor(Color::White);
            sandboxValues.setPosition(FONT_OFFSET,FONT_OFFSET * 7 + FONT_SIZE + IMG_SIZE);

            while(starterWindow.isOpen()) {
                if(gameStarted) {
                    starterWindow.close();
                    break;
                }

                Event event;
                while(starterWindow.pollEvent(event))
                    menuEventHandler(starterWindow,mainMenu,event);

                starterWindow.clear();
                starterWindow.draw(difficultyLevels);
                starterWindow.draw(sandboxValues);
                starterWindow.draw(mainMenu);
                starterWindow.display();
            }
            initializer = mainMenu.getInitializer();
        }

        if(!gameExit) {
            Board mainBoard(initializer.initWidth, initializer.initHeight, initializer.initBombs);
            gameLost = gameStarted = gameRestart = false;
            Visualizer visualizer(mainBoard);
            InfoBar infoBar(initializer.initWidth, 40, initializer.initBombs);

            if (!visualizer.load())
                return;
            if (!infoBar.load())
                return;

            RenderWindow gameWindow(VideoMode(visualizer.getWidth(),visualizer.getHeight()), "Saper",Style::Close | Style::Titlebar);
            gameWindow.setVerticalSyncEnabled(true);

            Clock clock;
            while (gameWindow.isOpen()) {

                Event event;
                while(gameWindow.pollEvent(event))
                    gameEventHandler(gameWindow,visualizer,infoBar,event);


                if(!gameStarted)
                    clock.restart();
                if(!gameLost && !visualizer.mapRevealed())
                    infoBar.timeUpdate((int)clock.getElapsedTime().asMicroseconds()/1000000);

                gameWindow.clear();
                gameWindow.draw(infoBar);
                gameWindow.draw(visualizer);
                gameWindow.display();

                if(gameRestart)
                    gameWindow.close();
            }
        }
    } while(!gameExit);
}