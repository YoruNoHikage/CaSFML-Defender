#include "../config.hpp"

#include "../game.hpp"
#include "character.hpp"

Character::Character(const sf::Texture& texture) : DrawableEntity(texture),
                                                   Collidable(),
                                                   Alive(),
                                                   _weapon(NULL),
                                                   _direction(1),
                                                   _velocity(0.1f),
                                                   _nearToCastle(false)
{
}

Character::~Character()
{
    if(_weapon != NULL)
        delete _weapon;
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

    _hitbox->setPosition(getPosition().x, getPosition().y);

    if(!isNearToCastle())
        goToCastle(elapsedTime);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    DrawableEntity::drawCurrent(target, states);
    if(_hitbox && Game::getContext().getDebug())
        _hitbox->drawDebug(target, states);
}

Weapon* Character::getWeapon()
{
    return _weapon;
}

bool Character::isNearToCastle() const
{
    return _nearToCastle;
}

void Character::nearToCastle(Castle& castle)
{
    _nearToCastle = true;
}

void Character::goToCastle(sf::Time elapsedTime)
{
    move(_velocity * elapsedTime.asMilliseconds(), 0);
}
