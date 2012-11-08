#include "config.hpp"

#include "castle.hpp"

Castle::Castle() : life(100)
{
}

Castle::~Castle()
{
    delete _hitbox;
}

void Castle::load(std::string filename)
{
    VisibleGameObject::load(filename);
    assert(isLoaded());

    _hitbox = new BoundingBoxHitbox(getDimension());
}

void Castle::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);

    _hitbox->setPosition(getPosition().x, getPosition().y); // TO FIX : change that because the castle never moves
}
