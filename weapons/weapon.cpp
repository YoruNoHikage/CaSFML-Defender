#include "../config.hpp"

#include "../game.hpp"
#include "weapon.hpp"

Weapon::Weapon() : _angle(0), _rechargingTime(sf::seconds(0.2f)), _elapsedTime(sf::seconds(0))
{
}

Weapon::~Weapon()
{
}

void Weapon::load(std::string filename)
{
    VisibleGameObject::load(filename);
    if(isLoaded())
    {
        // PROBLEM TO SOLVE : Fix the origin center when the scale isn't 1.f
        getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
    }
}

void Weapon::setAngle(float angle)
{
    _angle = angle;
}

void Weapon::shoot(sf::Time elapsedTime, sf::Vector2i location)
{
    if(_elapsedTime > _rechargingTime // if the weapon is not recharged, it's not possible to shoot
       && location.x <= getPosition().x) // and, of course, it's not possible to shoot behind the character
    {
        Shot *newShot = new Shot(location, this);
        newShot->load(IMAGES_PATH"shot.png");
        Game::addShot(newShot);

        _elapsedTime = sf::seconds(0);
    }
}

void Weapon::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);

    _elapsedTime += elapsedTime; // keeps elapsedTime in memory

    // computes the angle between the mouse's position and the object
    float deltaX = sf::Mouse::getPosition(Game::getWindow()).x - getPosition().x;
    float deltaY = sf::Mouse::getPosition(Game::getWindow()).y - getPosition().y;

    if(deltaX == 0)
        _angle = 0;
    else // rotates to be in the cursor's direction
        _angle = (std::atan(deltaY / deltaX) / (M_PI * 2)) * 360;

    if(isLoaded())
    {
        if(deltaX < 0) // forces the angle to be between pi / 2 and -pi / 2
            getSprite().rotate(_angle - getSprite().getRotation());
    }
}

float Weapon::getAngle() const
{
    return _angle;
}
