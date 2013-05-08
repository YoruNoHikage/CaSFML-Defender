#include "../config.hpp"

#include "enemymanager.hpp"
#include "../game.hpp"

EnemyManager::EnemyManager() : _generationTime(sf::seconds(1.f))
{
}

EnemyManager::~EnemyManager()
{
    std::for_each(_enemies.begin(), _enemies.end(), Deallocator<Enemy>());
}

void EnemyManager::generateEnemies()
{
    for(int i = 0 ; i < 5 ; i++)
    {
        Enemy* enemy = new Enemy();
        enemy->load("enemy.png");
        if(enemy->isLoaded())
        {
            enemy->setPosition(- enemy->getDimension().height, WINDOW_HEIGHT - enemy->getDimension().height - 50); // change 50
            _enemies.push_back(enemy);
        }
    }
}

void EnemyManager::getNewEnemies(sf::Time elapsedTime)
{
    if(Game::getContext().getEnemies().size() == 0)
        _waveOver = true;

    if(_enemies.size() == 0)
        generateEnemies();
    else if(_waveOver) // change that to do waves of enemies
    {
        _elapsedTime += elapsedTime;
        if(_elapsedTime > _generationTime)
        {
            Game::getContext().addEnemy(_enemies.front());
            _enemies.erase(_enemies.begin());

            _enemiesLeft++;
            _elapsedTime = sf::seconds(0);
        }

        if(_enemiesLeft == 5)
        {
            _enemiesLeft = 0;
            _waveOver = false;
        }
    }
}
