#ifndef CIRCLEHITBOX_HPP
#define CIRCLEHITBOX_HPP

#include "hitbox.hpp"

class CircleHitbox : public Hitbox
{
    public:
        CircleHitbox(int x, int y, float radius);
        CircleHitbox(sf::Vector2f pos, float radius);
        CircleHitbox(Circle circ);
        ~CircleHitbox();

        bool collide(int x, int y);
        bool collide(Circle circ);
        bool collide(sf::Rect<float> rect);

        void setPosition(int x, int y);

        Circle getCircle();

    private:
        Circle _circ;
};

#endif


