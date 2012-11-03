#ifndef GAME_HPP
#define GAME_HPP

#include "splashscreen/splashscreen.hpp"
#include "characters/character.hpp"
#include "landscape/background.hpp"
#include "castle.hpp"
#include "weapons/shot.hpp"

class Game
{
    public:
        Game();
        ~Game();

        static void start();
        static sf::RenderWindow& getWindow();
        const static sf::Event& getCurrentEvent();
        static std::list<Shot*> getShots();

        static void addShot(Shot* shot);

    private:
        static bool isExiting();
        static void gameLoop();

        static void showSplashScreen();

        static void updateAll();
        static void drawAll();

        enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

        static GameState _gameState;
        static sf::RenderWindow _mainWindow;
        static sf::Event _currentEvent;
        static sf::Clock _clock;

        static Character _character;
        static Castle _castle;
        static VisibleGameObject _ground;
        static Background _background;
        static std::list<Shot*> _shots;

        struct ShotsDeallocator
        {
            void operator()(const Shot* p) const
            {
                delete p;
            }
        };
};

#endif
