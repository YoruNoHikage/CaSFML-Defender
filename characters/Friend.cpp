#include "Friend.hpp"

Friend::Friend(const sf::Texture& texture) : Character(texture)
{
}

Friend::~Friend()
{
}

void Friend::loadAnimationsFromNode(Node& root)
{
    DrawableEntity::loadAnimationsFromNode(root);

    // We fill the entity's attributes
    int life = atoi(root.firstAttributeValue("life").c_str());
    setLife(life);

    /*////// Enemy's children //////

    // we set the healthbar
    _healthBar.setMaxValue(getLife());
    _healthBar.setPosition(getGlobalBounds().width / 2 - _healthBar.getGlobalBounds().width / 2,
                           - _healthBar.getGlobalBounds().height * 2);*/
}

void Friend::updateCurrent(sf::Time elapsedTime)
{
    Character::updateCurrent(elapsedTime);
}

void Friend::nearToCastle(Castle& castle)
{
    // ouf, saved
}
