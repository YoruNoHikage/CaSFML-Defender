#ifndef WAVE_HPP
#define WAVE_HPP

#include "../characters/enemy.hpp"

class Wave
{
    public:
        Wave();
        ~Wave();

        void addEnemy(Enemy* enemy);

        std::vector<Enemy*>& getEnemies();

    private:
        std::vector<Enemy*> _enemies;
};

#endif // WAVE_HPP
