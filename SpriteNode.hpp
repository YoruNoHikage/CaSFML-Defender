#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include "SceneNode.hpp"

class SpriteNode : public SceneNode
{
    public:
        SpriteNode();
        virtual ~SpriteNode();

        virtual sf::IntRect getRect() const;

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);
        virtual void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    protected:
        sf::Sprite _sprite;
};


#endif // SPRITENODE_HPP
