#include "../config.hpp"

#include "character.hpp"

Character::Character(const sf::Texture& texture) : DrawableEntity(texture),
                                                   _isAlive(true)
{
}

Character::~Character()
{
    if(_weapon != NULL)
        delete _weapon;
}

void Character::load(std::string filename)
{
    _weapon = NULL;
}

void Character::load(std::string filename, std::string fWeapon)
{
    _weapon = new Weapon();
    _weapon->load(fWeapon);
}

void Character::update(sf::Time elapsedTime)
{
    DrawableEntity::update(elapsedTime);
    if(_weapon != NULL)
        _weapon->update(elapsedTime);
}

void Character::attack(sf::Time elapsedTime)
{
}

void Character::draw(sf::RenderWindow& window)
{
    if(_weapon != NULL)
        _weapon->draw(window);
}

Weapon* Character::getWeapon()
{
    return _weapon;
}

bool Character::isAlive()
{
    return _isAlive;
}
