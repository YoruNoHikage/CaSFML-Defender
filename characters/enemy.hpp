#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../tools/node.hpp"
#include "character.hpp"

#include "../Alive.hpp"
#include "../BarDisplay.hpp"

class Enemy : public Character
{
    public:
        Enemy(const sf::Texture& texture);
        virtual ~Enemy();

        virtual void attack(sf::Time elapsedTime);

        virtual void loadAnimationsFromNode(Node& root);

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);

    private:
        BarDisplay _healthBar;
};

#endif
