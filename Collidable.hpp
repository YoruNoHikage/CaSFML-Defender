#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <SFML/System/NonCopyable.hpp>

#include "hitbox/hitbox.hpp"

class Collidable : sf::NonCopyable
{
    public:
        Collidable() : _hitbox(NULL) {};
        ~Collidable()
        {
            if(_hitbox != NULL)
                delete _hitbox;
        };

        bool collide(Collidable &object) { return _hitbox->collide(object.getHitbox()); };

        Hitbox* getHitbox() { return _hitbox; };
        void setHitbox(Hitbox* hitbox) { _hitbox = hitbox; };

    protected:
        Hitbox *_hitbox;
};


#endif // COLLIDABLE_HPP
