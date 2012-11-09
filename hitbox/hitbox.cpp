#include "../config.hpp"

#include "circlehitbox.hpp"
#include "boundingboxhitbox.hpp"

Hitbox::Hitbox()
{
}

Hitbox::~Hitbox()
{
}

// I know dynamic_cast is maybe a bad pratice but i'm not closed to suggestions :)
bool Hitbox::collide(Hitbox *hitbox)
{
    BoundingBoxHitbox* box = dynamic_cast<BoundingBoxHitbox*>(hitbox);
    if(box != NULL)
    {
        CircleHitbox* circle2 = dynamic_cast<CircleHitbox*>(this);
        if(circle2 != NULL)
            return circle2->collide(box->getBoundingBox());

        BoundingBoxHitbox* box2 = dynamic_cast<BoundingBoxHitbox*>(this);
        if(box2 != NULL)
            return box2->collide(box->getBoundingBox());

        return false; // if it's a box, it's useless to get out of the if
    }

    CircleHitbox* circle = dynamic_cast<CircleHitbox*>(hitbox);
    if(circle != NULL)
    {
        CircleHitbox* circle2 = dynamic_cast<CircleHitbox*>(this);
        if(circle2 != NULL)
            return circle2->collide(circle->getCircle());

        BoundingBoxHitbox* box2 = dynamic_cast<BoundingBoxHitbox*>(this);
        if(box2 != NULL)
            return box2->collide(circle->getCircle());

        return false; // the same (even if there's no instructions after :D)
    }

    return false;
}

bool Hitbox::collide(int x, int y)
{
}

bool Hitbox::collide(sf::Rect<float> rect)
{
}

bool Hitbox::collide(Circle circ)
{
}

void Hitbox::setPosition(int x, int y)
{
}

sf::Vector2f Hitbox::getPosition() const
{
    return sf::Vector2f(0,0);
}
