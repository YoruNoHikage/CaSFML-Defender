#ifndef GAME_HPP
#define GAME_HPP

#include "splashscreen/splashscreen.hpp"
#include "characters/player.hpp"
#include "characters/enemy.hpp"
#include "characters/enemymanager.hpp"
#include "landscape/background.hpp"
#include "landscape/ground.hpp"
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
        static std::list<Enemy*> getEnemies();

        static void addShot(Shot* shot);
        static void addEnemy(Enemy* enemy);

    private:
        static bool isExiting();
        static void gameLoop();

        static void showSplashScreen();

        static void updateAll();
        static void checkAllCollisions();
        static void drawAll();

        enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

        static GameState _gameState;
        static sf::RenderWindow _mainWindow;
        static sf::Event _currentEvent;
        static sf::Clock _clock;

        static Player _player;
        static Castle _castle;
        static Ground _ground;
        static Background _background;
        static std::list<Shot*> _shots;
        static std::list<Enemy*> _enemies; // enemies in game

        static EnemyManager _em;

        struct ShotsDeallocator
        {
            void operator()(const Shot* p) const
            {
                delete p;
            }
        };

        struct EnemiesDeallocator
        {
            void operator()(const Enemy* p) const
            {
                delete p;
            }
        };
};

#endif
