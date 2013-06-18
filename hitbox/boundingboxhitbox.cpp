#include "../config.hpp"

#include "boundingboxhitbox.hpp"

BoundingBoxHitbox::BoundingBoxHitbox(sf::Rect<float> box) : _boundingBox(box)
{
}

BoundingBoxHitbox::~BoundingBoxHitbox()
{
}

bool BoundingBoxHitbox::collide(sf::Rect<float> rect)
{
    // test with AABB if no rotation, ADD THE ROTATION TEST IF 0
    if(_boundingBox.intersects(rect))
        return true;

    return false;
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

sf::Rect<float> BoundingBoxHitbox::getBoundingBox()
{
    return _boundingBox;
}
