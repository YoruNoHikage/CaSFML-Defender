#include "../config.hpp"

#include "../tools/locator.hpp"

#include "../game.hpp"
#include "weapon.hpp"

Weapon::Weapon() : SpriteNode(),
                   _angle(0),
                   _rechargingTime(sf::seconds(0.2f)),
                   _elapsedTime(sf::seconds(0)),
                   _isLoaded(false)
{
}

Weapon::~Weapon()
{
}

void Weapon::load(std::string filename)
{
    ImageManager *im = Locator::getImageManager();
    sf::Texture* texture = im->getTexture(IMAGES_PATH + filename);
    if(texture == NULL)
        _isLoaded = false;
    else
    {
        _sprite.setTexture(*texture);
        _isLoaded = true;
    }
}

void Weapon::setAngle(float angle)
{
    _angle = angle;
}

void Weapon::shoot(sf::Time elapsedTime, sf::Vector2f location)
{
    if(_elapsedTime > _rechargingTime) // if the weapon is not recharged, it's not possible to shoot
    {
        Shot *newShot = new Shot(location, _angle, this);
        newShot->load("shot.png");
        Game::getContext().addShot(newShot);

        _elapsedTime = sf::Time::Zero;
    }
}

float Weapon::getAngle() const
{
    return _angle;
}

void Weapon::updateCurrent(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime; // keeps elapsedTime in memory

    // weapon's rotation is auto because it's a player's child
}
