#include "../config.hpp"

#include "enemy.hpp"

Enemy::Enemy() : _velocity(0.1f), _nearToCastle(false)
{
}

Enemy::~Enemy()
{
    if(_hitbox != NULL)
        delete _hitbox;
}

void Enemy::load(std::string filename)
{
    Character::load(filename);

    _hitbox = new BoundingBoxHitbox(getDimension());
}

void Enemy::load(std::string filename, std::string fWeapon)
{
    Character::load(filename, fWeapon);

    _hitbox = new BoundingBoxHitbox(getDimension());
}

void Enemy::update(sf::Time elapsedTime)
{
    Character::update(elapsedTime);
    if(!_nearToCastle)
        goToCastle(elapsedTime);
    else
        attack(elapsedTime);

    _hitbox->setPosition(getPosition().x, getPosition().y);
}

void Enemy::goToCastle(sf::Time elapsedTime)
{
    getSprite().move(_velocity * elapsedTime.asMilliseconds(), 0);
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
