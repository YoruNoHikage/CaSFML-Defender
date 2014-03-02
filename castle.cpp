#include "config.hpp"

#include "castle.hpp"

Castle::Castle() : life(100)
{
}

Castle::~Castle()
{
    delete Collidable::_hitbox;
    delete VisibleGameObject::_hitbox;
}

void Castle::load(std::string filename)
{
    VisibleGameObject::load(filename);
    assert(isLoaded());

    Collidable::_hitbox = new BoundingBoxHitbox(getDimension());
    VisibleGameObject::_hitbox = new BoundingBoxHitbox(getDimension());
}

void Castle::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);

    Collidable::_hitbox->setPosition(getPosition().x, getPosition().y); // TO FIX : change that because the castle never moves
    VisibleGameObject::_hitbox->setPosition(getPosition().x, getPosition().y); // TO FIX : change that because the castle never moves
}
