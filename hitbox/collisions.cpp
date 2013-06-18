#include "../config.hpp"

#include "hitbox.hpp"

bool circVsPoint(int x, int y, Circle circ)
{
    int d = (x - circ.x) * (x - circ.x) + (y - circ.y) * (y - circ.y);
    return d <= circ.radius * circ.radius;
}

bool circVsCirc(Circle circ)
{
    int d = (circ.x - circ.x) * (circ.x - circ.x) + (circ.y - circ.y) * (circ.y - circ.y);
    return d <= (circ.radius + circ.radius) * (circ.radius + circ.radius);
}

bool circVsRect(Circle circ, sf::Rect<float> rect)
{
    // we compute the circle's boundingbox
    sf::Rect<float> circleBox(circ.x - circ.radius, circ.y - circ.radius, circ.radius * 2, circ.radius * 2);

    // boundingbox vs boundingbox
	if(!circleBox.intersects(rect))
        return false;

    // point vs circle
    if(circVsPoint(rect.left, rect.top, circ) || circVsPoint(rect.left, rect.top + rect.height, circ)
    || circVsPoint(rect.left + rect.width, rect.top, circ) || circVsPoint(rect.left + rect.width, rect.top + rect.height, circ))
        return true;

    //point vs boundingbox (external function please)
    if(circ.x >= rect.left && circ.x < rect.left + rect.width
    && circ.y >= rect.top && circ.y < rect.top + rect.height)
        return true;

    //projection on a segment
    if(segmentProjection(circ, rect.left, rect.top, rect.left, rect.top + rect.height)
    || segmentProjection(circ, rect.left, rect.top, rect.left + rect.width, rect.top))
        return true;

    return false;
}

bool segmentProjection(Circle circ, float Ax, float Ay, float Bx, float By)
{
    float ACx = circ.x - Ax;
    float ACy = circ.y - Ay;
    float ABx = Bx - Ax;
    float ABy = By - Ay;
    float BCx = circ.x - Bx;
    float BCy = circ.y - By;
    float s1 = (ACx * ABx) + (ACy * ABy);
    float s2 = (BCx * ABx) + (BCy * ABy);
    if(s1 * s2 > 0)
        return false;
    return true;
}
