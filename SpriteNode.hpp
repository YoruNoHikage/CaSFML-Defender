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

        virtual sf::IntRect getTextureRect() const;
        virtual sf::FloatRect getGlobalBounds() const;
        virtual sf::FloatRect getLocalBounds() const;

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);
        virtual void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    protected:
        sf::Sprite _sprite;
};


#endif // SPRITENODE_HPP
