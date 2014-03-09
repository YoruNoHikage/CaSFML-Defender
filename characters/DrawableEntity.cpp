#include <iostream>
#include "DrawableEntity.hpp"

#include <SFML/Graphics/CircleShape.hpp> // debugging origin points

DrawableEntity::DrawableEntity(const sf::Texture& texture) : _animations(),
                                                             _currentAnimation(),
                                                             _texture(texture)
{
}

DrawableEntity::~DrawableEntity()
{
}

void DrawableEntity::createAnimation(const int name, const sf::IntRect& animationArea, const sf::IntRect& spriteArea, const sf::Time duration)
{
    sf::Sprite sprite(_texture, animationArea);

    _animations.insert(std::pair<const int, Animation>(name,Animation()));
    _animations[name].create(sprite, spriteArea, duration);
}

void DrawableEntity::setAnimation(const int name)
{
    _animations[_currentAnimation].reset();
    _currentAnimation = name;
}

void DrawableEntity::updateCurrent(sf::Time elapsedTime)
{
    _animations[_currentAnimation].update(elapsedTime);
}

void DrawableEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(_animations.size() != 0)
    {
        const Animation& anim = _animations.find(_currentAnimation)->second;
        target.draw(anim, states);

        // debug origin point
        sf::CircleShape debug(4);
        debug.setPosition(getOrigin());
        debug.setOrigin(4, 4);
        debug.setFillColor(sf::Color(0, 0, 255, 50));
        target.draw(debug, states);
    }
}

sf::IntRect DrawableEntity::getTextureRect() const
{
    const Animation& anim = _animations.find(_currentAnimation)->second;
    return anim.getTextureRect();
}

sf::FloatRect DrawableEntity::getGlobalBounds() const
{
    const Animation& anim = _animations.find(_currentAnimation)->second;
    return anim.getGlobalBounds();
}

sf::FloatRect DrawableEntity::getLocalBounds() const
{
    const Animation& anim = _animations.find(_currentAnimation)->second;
    return anim.getLocalBounds();
}
