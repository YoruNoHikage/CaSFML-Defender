#include "config.hpp"

#include "context.hpp"

Context::Context()
{
}

Context::~Context()
{
    std::for_each(_shots.begin(), _shots.end(), Deallocator<Shot>());
    std::for_each(_enemies.begin(), _enemies.end(), Deallocator<Enemy>());
}

std::list<Shot*>& Context::getShots()
{
    return _shots;
}

void Context::addShot(Shot* shot)
{
    _shots.push_back(shot);
}

std::list<Enemy*>& Context::getEnemies()
{
    return _enemies;
}

void Context::addEnemy(Enemy* enemy)
{
    _enemies.push_back(enemy);
}
