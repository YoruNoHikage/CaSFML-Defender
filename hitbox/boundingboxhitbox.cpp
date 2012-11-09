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
    std::cout << "oops, you have to write this function !" << std::endl;
    // test with AABB if no rotation, otherwise test OOB
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
