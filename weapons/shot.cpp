#include "../config.hpp"

#include "weapon.hpp"
#include "shot.hpp"

#include "../hitbox/circlehitbox.hpp"

Shot::Shot(sf::Vector2f location, Weapon *weapon) : _velocity(0.5f), _location(location), _weapon(weapon), _damage(1)
{
}

Shot::~Shot()
{
    if(_hitbox != NULL)
        delete _hitbox;
}

void Shot::load(std::string filename)
{
    VisibleGameObject::load(filename);
    assert(isLoaded());
    getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
    getSprite().setPosition(_weapon->getPosition().x - _weapon->getDimension().width / 2, _weapon->getPosition().y);

    _hitbox = new CircleHitbox(getPosition(), (getDimension().width + getDimension().height) / 4);

    _deltaY = getSprite().getPosition().y - _location.y;
    _deltaX = getSprite().getPosition().x - _location.x;
    _coeff = _deltaY / _deltaX; // director coefficient
}

void Shot::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);
    float distance = _velocity * elapsedTime.asMilliseconds(); // d = v * t, elementary my dear Watson !
    float x = distance / std::sqrt(1 + _coeff * _coeff); // from AB^2 = |xA - xB|^2 + |yA - yB|^2
    if(_deltaX > 0) // For one corner in the screen
        x = -x;

    getSprite().move(x, x * _coeff);

    _hitbox->setPosition(getPosition().x, getPosition().y);
}

bool Shot::hasToBeRemoved()
{
    if(!isAlive())
        return true;
    if(getPosition().x > VIEW_WIDTH + getDimension().width
       || getPosition().x + getDimension().width < 0
       || getPosition().y > VIEW_HEIGHT + getDimension().height
       || getPosition().y + getDimension().height < 0)
        return true;
    return false;
}

void Shot::die()
{
    _isAlive = false;
}
