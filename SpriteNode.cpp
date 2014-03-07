#include "SpriteNode.hpp"

SpriteNode::SpriteNode() : _sprite()
{}

SpriteNode::~SpriteNode()
{}

sf::IntRect SpriteNode::getRect() const
{
    return _sprite.getTextureRect();
}

void SpriteNode::updateCurrent(sf::Time elapsedTime)
{
    // nothing to update here
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
