#include "../config.hpp"

#include "character.hpp"

Character::Character()
{
}

Character::~Character()
{
    if(_weapon != NULL)
        delete _weapon;
}

void Character::load(std::string filename)
{
    VisibleGameObject::load(filename);
    assert(isLoaded());
    _weapon = NULL;
}

void Character::load(std::string filename, std::string fWeapon)
{
    VisibleGameObject::load(filename);
    assert(isLoaded());
    _weapon = new Weapon();
    _weapon->load(fWeapon);
}

void Character::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);

    if(_weapon != NULL)
        _weapon->update(elapsedTime);
}

void Character::attack(sf::Time elapsedTime)
{
}

void Character::draw(sf::RenderWindow& window)
{
    VisibleGameObject::draw(window);
    if(_weapon != NULL)
        _weapon->draw(window);
}

Weapon* Character::getWeapon()
{
    return _weapon;
}
