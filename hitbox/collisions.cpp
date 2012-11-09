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

    // boundingbox vs boundingbox (to put in a external function if possible)
    if((rect.left >= circleBox.left + circleBox.width)
	|| (rect.left + rect.width <= circleBox.top)
	|| (rect.top >= circleBox.top + circleBox.height)
	|| (rect.top + rect.height <= circleBox.top))
        return false;

    // point vs circle
    if(circVsPoint(rect.left, rect.top, circ) || circVsPoint(rect.left, rect.top + rect.height, circ)
    || circVsPoint(rect.left + rect.width, rect.top, circ) || circVsPoint(rect.left + rect.width, rect.top + rect.height, circ))
        return true;

    //point vs boundingbox (the same)
    if(circ.x >= rect.left && circ.x < rect.left + rect.width
    && circ.y >= rect.top && circ.y < rect.top + rect.height)
        return true;

    //projection on a segment
    if(!(((circ.x - rect.left) * (rect.left - rect.left) + (circ.y - rect.top) * (rect.top + rect.height - rect.top)) * ((circ.x - rect.left) * (rect.left - rect.left) + (circ.y - rect.top + rect.height) * (rect.top + rect.height - rect.top)) > 0)
    || !(((circ.x - rect.left) * (rect.left + rect.width - rect.left) + (circ.y - rect.top) * (rect.top - rect.top)) * ((circ.x - rect.left + rect.width) * (rect.left + rect.width - rect.left) + (circ.y - rect.top) * (rect.top - rect.top)) > 0))
        return true;

    return false;
}
