#include "../config.hpp"

#include "enemy.hpp"

Enemy::Enemy(const sf::Texture& texture) : Character(texture),
                                           _velocity(0.1f),
                                           _nearToCastle(false)
{
}

Enemy::~Enemy()
{
}

void Enemy::load(std::string filename)
{
    Character::load(filename);
}

void Enemy::load(std::string filename, std::string fWeapon)
{
    Character::load(filename, fWeapon);
}

void Enemy::updateCurrent(sf::Time elapsedTime)
{
    Character::updateCurrent(elapsedTime);
    if(!_nearToCastle)
        goToCastle(elapsedTime);
    else
        attack(elapsedTime);

    _hitbox->setPosition(getPosition().x, getPosition().y);
}

void Enemy::goToCastle(sf::Time elapsedTime)
{
    move(_velocity * elapsedTime.asMilliseconds(), 0);
}

void Enemy::nearToCastle()
{
    _nearToCastle = true;
}

bool Enemy::isNearToCastle() const
{
    return _nearToCastle;
}

void Enemy::attack(sf::Time elapsedTime)
{
    //if(getWeapon() != NULL)
        // attack avec l'arme
}

void Enemy::die()
{
    _isAlive = false;
}
