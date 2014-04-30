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

        enum Type {ATTACK = DrawableEntity::BLINK + 1}; // used not to have the same values

        virtual void loadAnimationsFromNode(Node& root);
        virtual void loadWeaponFromNode(Node& root);

        virtual void nearToCastle(Castle& castle);

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);

    private:
        BarDisplay _healthBar;

        Castle* _targetCastle;

        /// Weapon is currently integrated in the enemy
        int _damages;
};

#endif
