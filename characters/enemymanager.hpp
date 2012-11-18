#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include "enemy.hpp"

class EnemyManager
{
    public:
        EnemyManager();
        ~EnemyManager();

        void generateEnemies(); // for survival mode
        void getNewEnemies(sf::Time elapsedTime);

    private:
        std::list<Enemy*> _enemies; // waiting to be added in the game
        sf::Time _generationTime, _elapsedTime;
        bool _waveOver;
        unsigned int _enemiesLeft;

        struct EnemiesDeallocator
        {
            void operator()(const Enemy* p) const
            {
                delete p;
            }
        };
};

#endif
