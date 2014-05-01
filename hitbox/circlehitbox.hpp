#ifndef CIRCLEHITBOX_HPP
#define CIRCLEHITBOX_HPP

#include "hitbox.hpp"

class CircleHitbox : public Hitbox
{
    public:
        CircleHitbox(int x, int y, float radius);
        CircleHitbox(sf::Vector2f pos, float radius);
        ~CircleHitbox();

        bool collide(Hitbox* hitbox);

        bool collide(int x, int y);
        bool collide(sf::Rect<float> rect);
        bool collide(Circle circ);

        Circle getCircle();

        void drawDebug(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Circle _circ;
};

#endif


