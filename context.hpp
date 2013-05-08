#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "characters/enemy.hpp"
#include "weapons/shot.hpp"

class Context {
    public:
        Context();
        ~Context();
        sf::RenderWindow& getApp() { return _mainWindow;};

        std::list<Shot*>& getShots();
        std::list<Enemy*>& getEnemies();

        void addShot(Shot* shot);
        void addEnemy(Enemy* enemy);

    private:
        sf::RenderWindow _mainWindow;
        std::list<Shot*> _shots;
        std::list<Enemy*> _enemies; // enemies in game
};

#endif
