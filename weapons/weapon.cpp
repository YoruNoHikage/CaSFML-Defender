#include "../config.hpp"

#include "../game.hpp"
#include "weapon.hpp"

Weapon::Weapon() : _angle(0)
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
        getSprite().setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }
}

void Weapon::setAngle(float angle)
{
    _angle = angle;
}

void Weapon::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);

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
