#include "../config.hpp"

#include "weapon.hpp"
#include "shot.hpp"

Shot::Shot(sf::Vector2i location, Weapon *weapon) : _velocity(0.5f), _location(location), _weapon(weapon), _damage(1)
{
}

Shot::~Shot()
{
    std::cout << "shot deleted" << std::endl;
}

void Shot::load(std::string filename)
{
    VisibleGameObject::load(filename);
    assert(isLoaded());
    getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
    getSprite().setPosition(_weapon->getPosition().x - _weapon->getDimension().width / 2, _weapon->getPosition().y);

    _deltaY = getSprite().getPosition().y - _location.y;
    _deltaX = getSprite().getPosition().x - _location.x;
    _coeff = _deltaY / _deltaX; // director coefficient
}

void Shot::update(sf::Time elapsedTime)
{
    float distance = _velocity * elapsedTime.asMilliseconds(); // d = v * t, elementary my dear Watson !
    float x = distance / std::sqrt(1 + _coeff * _coeff); // from AB^2 = |xA - xB|^2 + |yA - yB|^2
    if(_deltaX > 0) // For one corner in the screen
        x = -x;

    getSprite().move(x, x * _coeff);
}

bool Shot::hasToBeRemoved()
{
    if(getPosition().x > WINDOW_WIDTH + getDimension().width
       || getPosition().x + getDimension().width < 0
       || getPosition().y > WINDOW_HEIGHT + getDimension().height
       || getPosition().y + getDimension().height < 0)
        return true;
    return false;
}
