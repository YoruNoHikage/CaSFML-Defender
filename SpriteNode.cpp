#include "SpriteNode.hpp"

SpriteNode::SpriteNode() : _sprite()
{}

SpriteNode::~SpriteNode()
{}

sf::IntRect SpriteNode::getTextureRect() const
{
    return _sprite.getTextureRect();
}

sf::FloatRect SpriteNode::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

sf::FloatRect SpriteNode::getLocalBounds() const
{
    return _sprite.getLocalBounds();
}

void SpriteNode::updateCurrent(sf::Time elapsedTime)
{
    // nothing to update here
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
