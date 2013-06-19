#ifndef GAME_HPP
#define GAME_HPP

#include "screens/splashscreen.hpp"
#include "characters/player.hpp"
#include "characters/enemymanager.hpp"
#include "landscape/background.hpp"
#include "landscape/ground.hpp"
#include "castle.hpp"

class Game
{
    public:
        Game();
        virtual ~Game();

        void start();

        static Context& getContext();

    private:
        bool isExiting();
        void gameLoop();

        void showSplashScreen();

        void updateAll();
        void checkAllCollisions();
        void drawAll();

        enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

        GameState _gameState;
        sf::Event _currentEvent;
        sf::Clock _clock;

        Player _player;
        Castle _castle;
        Ground _ground;
        Background _background;

        EnemyManager _em;
};

#endif
