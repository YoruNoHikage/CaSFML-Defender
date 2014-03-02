#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../SceneNode.hpp"
#include "character.hpp"

class Player : public Character
{
    public:
        Player(const sf::Texture& texture);
        ~Player();

        void attack(sf::Time elapsedTime, sf::Vector2f location);

    private:

        void updateCurrent(sf::Time elapsedTime);

        void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    private:
        DrawableEntity _head,
                       _body,
                       _arm,
                       _foot;
};

#endif

