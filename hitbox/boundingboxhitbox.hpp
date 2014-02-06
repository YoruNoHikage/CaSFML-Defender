#ifndef BOUNDINGBOXHITBOX_HPP
#define BOUNDINGBOXHITBOX_HPP

#include "circlehitbox.hpp"

class BoundingBoxHitbox : public Hitbox
{
    public:
        BoundingBoxHitbox(sf::Rect<float> box);
        ~BoundingBoxHitbox();

        bool collide(Hitbox* hitbox);

        bool collide(int x, int y);
        bool collide(sf::Rect<float> rect);
        bool collide(Circle circ);

        void setPosition(int x, int y);
        sf::Vector2f getPosition() const;

        sf::Rect<float> getBoundingBox() const;

        void drawDebug(sf::RenderWindow& window) const;

    private:
        sf::Rect<float> _boundingBox;
};

#endif
