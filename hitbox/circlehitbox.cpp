#include "../config.hpp"

#include <SFML/Graphics/CircleShape.hpp>

#include "circlehitbox.hpp"

CircleHitbox::CircleHitbox(int x, int y, float radius)
{
    _circ.x = x;
    _circ.y = y;
    _circ.radius = radius;
}

CircleHitbox::CircleHitbox(sf::Vector2f pos, float radius)
{
    _circ.x = pos.x;
    _circ.y = pos.y;
    _circ.radius = radius;
}

CircleHitbox::CircleHitbox(Circle circ) : _circ(circ)
{
}

CircleHitbox::~CircleHitbox()
{
}

bool CircleHitbox::collide(Hitbox* hitbox)
{
    hitbox->collide(_circ);
}

bool CircleHitbox::collide(int x, int y)
{
    return circVsPoint(x, y, getCircle());
}

bool CircleHitbox::collide(sf::Rect<float> rect)
{
    return circVsRect(getCircle(), rect);
}

bool CircleHitbox::collide(Circle circ)
{
    return circVsCirc(circ);
}

void CircleHitbox::setPosition(int x, int y)
{
    _circ.x = x;
    _circ.y = y;
}

sf::Vector2f CircleHitbox::getPosition() const
{
    return sf::Vector2f(_circ.x, _circ.y);
}

Circle CircleHitbox::getCircle()
{
    return _circ;
}

void CircleHitbox::drawDebug(sf::RenderWindow& window) const
{
    sf::CircleShape debugCirc(_circ.radius);
    debugCirc.setFillColor(sf::Color(0, 0, 255, 50));
    debugCirc.setOutlineThickness(2);
    debugCirc.setOutlineColor(sf::Color::Blue);
    debugCirc.setOrigin(_circ.radius, _circ.radius);
    debugCirc.setPosition(_circ.x, _circ.y);

    window.draw(debugCirc);
}

void CircleHitbox::drawDebug(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape debugCirc(_circ.radius);
    debugCirc.setFillColor(sf::Color(0, 0, 255, 50));
    debugCirc.setOutlineThickness(2);
    debugCirc.setOutlineColor(sf::Color::Blue);
    debugCirc.setOrigin(_circ.radius, _circ.radius);
    debugCirc.setPosition(_circ.x, _circ.y);

    target.draw(debugCirc, sf::RenderStates::Default);
}
