#include "../config.hpp"

#include "enemymanager.hpp"
#include "../game.hpp"

EnemyManager::EnemyManager() : _generationTime(sf::seconds(1.f)), _noMoreEnemies(false), _enemiesLeft(0)
{
}

EnemyManager::~EnemyManager()
{
    std::for_each(_enemies.begin(), _enemies.end(), Deallocator<Enemy>());
}

void EnemyManager::generateEnemies()
{
    Wave* newWave = Game::getContext().getLevel().getNextWave();
    if(newWave != NULL)
    {
        while(newWave->getEnemies().size() > 0)
        {
            Enemy* enemy = newWave->getEnemies().front();
            newWave->getEnemies().erase(newWave->getEnemies().begin());
            _enemies.push_back(enemy);
        }
    }
    else
        _noMoreEnemies = true;
}

void EnemyManager::getNewEnemies(sf::Time elapsedTime)
{
    if(Game::getContext().getEnemies().size() == 0)
        _waveOver = true;

    if(_enemies.size() == 0)
        generateEnemies();
    else if(_waveOver)
    {
        _elapsedTime += elapsedTime;
        if(_elapsedTime > _generationTime)
        {
            Game::getContext().addEnemy(_enemies.front());
            _enemies.erase(_enemies.begin());

            _elapsedTime = sf::Time::Zero;
        }

        if(_enemies.size() == 0)
            _waveOver = false;
    }
}
