#include "../config.hpp"

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

bool CircleHitbox::collide(int x, int y)
{
    return circVsPoint(x, y, getCircle());
}

bool CircleHitbox::collide(Circle circ)
{
    return circVsCirc(circ);
}

bool CircleHitbox::collide(sf::Rect<float> rect)
{
    return circVsRect(getCircle(), rect);
}

void CircleHitbox::setPosition(int x, int y)
{
    _circ.x = x;
    _circ.y = y;
}

Circle CircleHitbox::getCircle()
{
    return _circ;
}
