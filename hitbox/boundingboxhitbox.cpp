#include "../config.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "boundingboxhitbox.hpp"

BoundingBoxHitbox::BoundingBoxHitbox(sf::Vector2f pos, sf::Rect<float> box) : _boundingBox(box)
{
    setPosition(pos);
}

BoundingBoxHitbox::~BoundingBoxHitbox()
{
}

bool BoundingBoxHitbox::collide(Hitbox* hitbox)
{
    return hitbox->collide(getBoundingBox());
}

bool BoundingBoxHitbox::collide(int x, int y)
{
    return getBoundingBox().contains(x, y);
}

bool BoundingBoxHitbox::collide(sf::Rect<float> rect)
{
    return getBoundingBox().intersects(rect);
}

bool BoundingBoxHitbox::collide(Circle circ)
{
    return circVsRect(circ, getBoundingBox());
}

sf::Rect<float> BoundingBoxHitbox::getBoundingBox() const
{
    return getTransform().transformRect(_boundingBox);
}

void BoundingBoxHitbox::drawDebug(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::FloatRect box = getBoundingBox();
    sf::RectangleShape debugRect(sf::Vector2f(box.width, box.height));
    debugRect.setFillColor(sf::Color(0, 0, 255, 50));
    debugRect.setOutlineThickness(2);
    debugRect.setOutlineColor(sf::Color::Blue);
    debugRect.setPosition(getBoundingBox().left, getBoundingBox().top);

    target.draw(debugRect, sf::RenderStates::Default);
}
