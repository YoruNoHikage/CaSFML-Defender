#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"

class Player : public Character
{
    public:
        Player(const sf::Texture& texture);
        ~Player();

        void update(sf::Time elapsedTime);
        void attack(sf::Time elapsedTime, sf::Vector2f location);

    private:
};

#endif

