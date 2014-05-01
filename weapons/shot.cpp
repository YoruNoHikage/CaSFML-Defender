#include "../config.hpp"

#include <cmath>

#include "../tools/locator.hpp"

#include "../game.hpp"
#include "weapon.hpp"
#include "shot.hpp"

#include "../hitbox/circlehitbox.hpp"

Shot::Shot(sf::Vector2f location, float angle, Weapon *weapon) : SpriteNode(),
                                                                 Collidable(),
                                                                 _damage(1),
                                                                 _velocity(0.5f),
                                                                 _location(location),
                                                                 _angle(angle),
                                                                 _weapon(weapon),
                                                                 _isLoaded(false),
                                                                 _isAlive(true)
{
    sf::Vector2f position(_weapon->getWorldPosition().x, _weapon->getWorldPosition().y);
    sf::Vector2f delta(position - location);
    _angle = (std::atan(delta.y / delta.x) / (M_PI * 2)) * 360;
    setRotation(_angle);
}

Shot::~Shot()
{
}

void Shot::load(std::string filename)
{
    ImageManager *im = Locator::getImageManager();
    sf::Texture* texture = im->getTexture(IMAGES_PATH + filename);
    if(texture == NULL)
        _isLoaded = false;
    else
    {
        _sprite.setTexture(*texture, true);
        _isLoaded = true;
    }

    setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
    setPosition(_weapon->getWorldPosition().x, _weapon->getWorldPosition().y);

    _hitbox = new CircleHitbox(getPosition(), (getGlobalBounds().width + getGlobalBounds().height) / 4);

    _deltaY = getPosition().y - _location.y;
    _deltaX = getPosition().x - _location.x;
    _coeff = _deltaY / _deltaX; // director coefficient

    Log::write(Log::LOG_INFO, "Shot loaded : position " + toString(getPosition()) + toString(getGlobalBounds()));
}

bool Shot::hasToBeRemoved()
{
    if(!_isAlive)
    {
        Log::write(Log::LOG_INFO, "Shot dead");
        return true;
    }
    if(getPosition().x > VIEW_WIDTH + getGlobalBounds().width
       || getPosition().x + getGlobalBounds().width < 0
       || getPosition().y > VIEW_HEIGHT + getGlobalBounds().height
       || getPosition().y + getGlobalBounds().height < 0)
    {
        Log::write(Log::LOG_INFO, "Shot out of bounds");
        return true;
    }
    return false;
}

void Shot::die()
{
    _isAlive = false;
}

void Shot::updateCurrent(sf::Time elapsedTime)
{
    if(_isAlive)
    {
        float distance = _velocity * elapsedTime.asMilliseconds(); // d = v * t, elementary my dear Watson !
        float x = distance / std::sqrt(1 + _coeff * _coeff); // from AB^2 = |xA - xB|^2 + |yA - yB|^2
        if(_deltaX > 0) // For one corner in the screen
            x = -x;

        move(x, x * _coeff);

        _hitbox->setPosition(getPosition().x, getPosition().y);
    }
}

void Shot::drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const
{
    SpriteNode::drawCurrent(target, states);
    if(_hitbox && Game::getContext().getDebug())
        _hitbox->drawDebug(target, states);
}
