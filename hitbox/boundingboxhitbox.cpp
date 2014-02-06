#include "../config.hpp"

#include "boundingboxhitbox.hpp"

BoundingBoxHitbox::BoundingBoxHitbox(sf::Rect<float> box) : _boundingBox(box)
{
}

BoundingBoxHitbox::~BoundingBoxHitbox()
{
}

bool BoundingBoxHitbox::collide(Hitbox* hitbox)
{
    hitbox->collide(_boundingBox);
}

bool BoundingBoxHitbox::collide(int x, int y)
{
    return _boundingBox.contains(x, y);
}

bool BoundingBoxHitbox::collide(sf::Rect<float> rect)
{
    return _boundingBox.intersects(rect);
}

bool BoundingBoxHitbox::collide(Circle circ)
{
    return circVsRect(circ, getBoundingBox());
}

void BoundingBoxHitbox::setPosition(int x, int y)
{
    _boundingBox.left = x;
    _boundingBox.top = y;
}

sf::Vector2f BoundingBoxHitbox::getPosition() const
{
    return sf::Vector2f(_boundingBox.left, _boundingBox.top);
}

sf::Rect<float> BoundingBoxHitbox::getBoundingBox() const
{
    return _boundingBox;
}

void BoundingBoxHitbox::drawDebug(sf::RenderWindow& window) const
{
    sf::RectangleShape debugRect(sf::Vector2f(_boundingBox.width, _boundingBox.height));
    debugRect.setFillColor(sf::Color(0, 0, 255, 50));
    debugRect.setOutlineThickness(2);
    debugRect.setOutlineColor(sf::Color::Blue);
    debugRect.setPosition(_boundingBox.left, _boundingBox.top);

    window.draw(debugRect);
}
