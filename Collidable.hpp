#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include "hitbox/hitbox.hpp"

class Collidable
{
    public:
        virtual ~Collidable() {};

        virtual bool collide(Collidable &object) { return _hitbox->collide(object.getHitbox()); };

        virtual Hitbox* getHitbox() { return _hitbox; };

    protected:
        Hitbox *_hitbox;
};


#endif // COLLIDABLE_HPP
