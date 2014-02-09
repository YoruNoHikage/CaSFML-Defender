#include <iostream>
#include "DrawableEntity.hpp"

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

void DrawableEntity::update(sf::Time elapsedTime)
{
    _animations[_currentAnimation].update(elapsedTime);
}

void DrawableEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(_animations.size() != 0)
    {
        states.transform *= getTransform();
        const Animation& anim = _animations.find(_currentAnimation)->second;
        target.draw(anim, states);
    }
}
