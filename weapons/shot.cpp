#include "../config.hpp"

#include "shot.hpp"

Shot::Shot(sf::Vector2i location) : _location(location), _velocity(0.5f), _damage(1)
{
    load(IMAGES_PATH"shot.png");
    assert(isLoaded());
    getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
    getSprite().setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    _deltaY = getSprite().getPosition().y - _location.y;
    _deltaX = getSprite().getPosition().x - _location.x;
    _coeff = _deltaY / _deltaX; // director coefficient
}

Shot::~Shot()
{
}

void Shot::update(sf::Time elapsedTime)
{
    float distance = _velocity * elapsedTime.asMilliseconds(); // d = v * t, elementary my dear Watson !
    float x = distance / std::sqrt(1 + _coeff * _coeff); // from AB^2 = |xA - xB|^2 + |yA - yB|^2
    if(_deltaX > 0) // For one corner in the screen
        x = -x;

    getSprite().move(x, x * _coeff);
}
