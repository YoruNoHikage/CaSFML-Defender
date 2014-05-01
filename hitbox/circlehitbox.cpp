#include "../config.hpp"

#include <SFML/Graphics/CircleShape.hpp>

#include "circlehitbox.hpp"

CircleHitbox::CircleHitbox(int x, int y, float radius)
{
    setPosition(x, y);
    _circ.radius = radius;
}

CircleHitbox::CircleHitbox(sf::Vector2f pos, float radius)
{
    setPosition(pos);
    _circ.radius = radius;
}

CircleHitbox::~CircleHitbox()
{
}

bool CircleHitbox::collide(Hitbox* hitbox)
{
    return hitbox->collide(getCircle());
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

Circle CircleHitbox::getCircle()
{
    _circ.x = getPosition().x;
    _circ.y = getPosition().y;
    return _circ;
}

void CircleHitbox::drawDebug(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape debugCirc(_circ.radius);
    debugCirc.setFillColor(sf::Color(0, 0, 255, 50));
    debugCirc.setOutlineThickness(2);
    debugCirc.setOutlineColor(sf::Color::Blue);
    debugCirc.setOrigin(_circ.radius, _circ.radius);
    debugCirc.setPosition(getPosition());

    target.draw(debugCirc, sf::RenderStates::Default);
}
