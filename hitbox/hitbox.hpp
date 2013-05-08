#ifndef HITBOX_HPP
#define HITBOX_HPP

struct Circle
{
    int x, y;
    float radius;
};

// Collisions functions shared between the classes
bool circVsPoint(int x, int y, Circle circ);
bool circVsCirc(Circle circ);
bool circVsRect(Circle circ, sf::Rect<float> rect);
bool AABBvSAABB(sf::Rect<float> rect1, sf::Rect<float> rect2);
bool segmentProjection(Circle circ, float Ax, float Ay, float Bx, float By);

class Hitbox
{
    public:
        Hitbox();
        virtual ~Hitbox();

        virtual bool collide(Hitbox *hitbox);

        virtual bool collide(int x, int y);
        virtual bool collide(sf::Rect<float> rect);
        virtual bool collide(Circle circ);

        virtual void setPosition(int x, int y);

        virtual sf::Vector2f getPosition() const;
};

#endif