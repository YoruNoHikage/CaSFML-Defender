#include "../config.hpp"

#include <stdexcept>

#include "enemy.hpp"

Enemy::Enemy(const sf::Texture& texture) : Character(texture),
                                           _healthBar()
{
    attachChild(&_healthBar);
}

Enemy::~Enemy()
{
}

void Enemy::updateCurrent(sf::Time elapsedTime)
{
    Character::updateCurrent(elapsedTime);

    if(isNearToCastle())
        attack(elapsedTime);

    _healthBar.setValue(getLife());
}

void Enemy::attack(sf::Time elapsedTime)
{
    //if(getWeapon() != NULL)
        // attack avec l'arme
}

void Enemy::loadAnimationsFromNode(Node& root)
{
    DrawableEntity::loadAnimationsFromNode(root);

    // We fill the entity's attributes
    int life = atoi(root.firstAttributeValue("life").c_str());
    setLife(life);

    ////// Enemy's children //////

    // we set the healthbar
    _healthBar.setMaxValue(getLife());
    _healthBar.setPosition(getGlobalBounds().width / 2 - _healthBar.getGlobalBounds().width / 2,
                           - _healthBar.getGlobalBounds().height * 2);
}
