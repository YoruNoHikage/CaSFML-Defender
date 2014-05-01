#ifndef HITBOX_HPP
#define HITBOX_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

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

class Hitbox : public sf::Transformable
{
    public:
        virtual ~Hitbox(){}

        virtual bool collide(Hitbox *hitbox) = 0;

        virtual bool collide(int x, int y) = 0;
        virtual bool collide(sf::Rect<float> rect) = 0;
        virtual bool collide(Circle circ) = 0;

        virtual void drawDebug(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

#endif
