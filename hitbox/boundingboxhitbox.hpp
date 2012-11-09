#ifndef BOUNDINGBOXHITBOX_HPP
#define BOUNDINGBOXHITBOX_HPP

#include "circlehitbox.hpp"

class BoundingBoxHitbox : public Hitbox
{
    public:
        BoundingBoxHitbox(sf::Rect<float> box);
        ~BoundingBoxHitbox();

        bool collide(sf::Rect<float> rect);
        bool collide(Circle circ);

        void setPosition(int x, int y);

        sf::Rect<float> getBoundingBox();

    private:
        sf::Rect<float> _boundingBox;
};

#endif
