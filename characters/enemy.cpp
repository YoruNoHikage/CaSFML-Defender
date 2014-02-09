#include "../config.hpp"

#include "enemy.hpp"

Enemy::Enemy(const sf::Texture& texture) : Character(texture),
                                           _velocity(0.1f),
                                           _nearToCastle(false)
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

    DrawableEntity::createAnimation(Enemy::BLINK, sf::IntRect(0, 0, 100, 100), sf::IntRect(0, 0, 50, 100), sf::seconds(1));
    DrawableEntity::setAnimation(Enemy::BLINK);
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

    DrawableEntity::update(elapsedTime);

    _hitbox->setPosition(VisibleGameObject::getPosition().x, VisibleGameObject::getPosition().y);
}

void Enemy::goToCastle(sf::Time elapsedTime)
{
    getSprite().move(_velocity * elapsedTime.asMilliseconds(), 0); ///@todo: delete
    DrawableEntity::move(_velocity * elapsedTime.asMilliseconds(), 0);
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
