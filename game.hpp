#ifndef GAME_HPP
#define GAME_HPP

#include "gameobjectmanager.hpp"

class Game
{

    public:
        static void start();
        static sf::RenderWindow& getWindow();
        const static sf::Event& getCurrentEvent();

    private:
        static bool isExiting();
        static void gameLoop();

        static void showSplashScreen();

        enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

        static GameState _gameState;
        static sf::RenderWindow _mainWindow;
        static sf::Event _currentEvent;
        static sf::Clock _clock;

        static GameObjectManager _gameObjectManager;
};

#endif
