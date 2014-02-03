#include "../config.hpp"

#include "ground.hpp"

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::load(std::string filename)
{
    VisibleGameObject::load(filename);
    getSprite().setPosition(0, VIEW_HEIGHT - getDimension().height);

    sf::Rect<float> rect(getPosition().x,
                         getPosition().y + getDimension().height / 2, // the collision is in the ground's middle
                         getDimension().width,
                         getDimension().height / 2);
    _hitbox = new BoundingBoxHitbox(rect);
}
