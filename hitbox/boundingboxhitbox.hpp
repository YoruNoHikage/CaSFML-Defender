#ifndef BOUNDINGBOXHITBOX_HPP
#define BOUNDINGBOXHITBOX_HPP

#include "circlehitbox.hpp"

class BoundingBoxHitbox : public Hitbox
{
    public:
        BoundingBoxHitbox(sf::Vector2f pos, sf::Rect<float> box);
        ~BoundingBoxHitbox();

        bool collide(Hitbox* hitbox);

        bool collide(int x, int y);
        bool collide(sf::Rect<float> rect);
        bool collide(Circle circ);

        sf::Rect<float> getBoundingBox() const;

        void drawDebug(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Rect<float> _boundingBox;
};

#endif
