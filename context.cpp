#include "config.hpp"

#include "context.hpp"

Context::Context() : _mainWindow(),
                     _shots(),
                     _enemies(),
                     _level(_mainWindow),
                     _isDebug(false)
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

bool Context::getDebug()
{
    return _isDebug;
}

void Context::setDebug(bool debug)
{
    _isDebug = debug;
}

