#include "../config.hpp"

#include "../game.hpp"
#include "weapon.hpp"

Weapon::Weapon() : _angle(0),
                   _rechargingTime(sf::seconds(0.2f)),
                   _elapsedTime(sf::seconds(0)),
                   _sprite(),
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
        Log::write(Log::LOG_INFO, "Weapon loaded : " + filename);
        //getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
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

void Weapon::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(_isLoaded)
    {
        const sf::Sprite& sprite = _sprite;
        target.draw(sprite, states);
    }
}
