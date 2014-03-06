#include "../config.hpp"

#include "../game.hpp"
#include "character.hpp"

Character::Character(const sf::Texture& texture) : DrawableEntity(texture),
                                                   Collidable(),
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
    attachChild(_weapon);
}

void Character::updateCurrent(sf::Time elapsedTime)
{
    DrawableEntity::updateCurrent(elapsedTime);
    if(_weapon != NULL)
        _weapon->update(elapsedTime);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    DrawableEntity::drawCurrent(target, states);
    if(_hitbox && Game::getContext().getDebug())
        _hitbox->drawDebug(target, states);
}

void Character::attack(sf::Time elapsedTime)
{
}

Weapon* Character::getWeapon()
{
    return _weapon;
}

bool Character::isAlive()
{
    return _isAlive;
}
