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
    Log::write(Log::LOG_INFO, "Collision BbHb vs Hb : " + toString(_boundingBox.top));
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
