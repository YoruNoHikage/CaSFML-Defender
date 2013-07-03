#include "../config.hpp"

#include "wave.hpp"

Wave::Wave()
{
}

Wave::~Wave()
{
    std::for_each(_enemies.begin(), _enemies.end(), Deallocator<Enemy>());
}

void Wave::addEnemy(Enemy* enemy)
{
    _enemies.push_back(enemy);
}

std::vector<Enemy*>& Wave::getEnemies()
{
    return _enemies;
}
