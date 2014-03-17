#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../tools/node.hpp"
#include "character.hpp"

#include "../Alive.hpp"
#include "../BarDisplay.hpp"

class Enemy : public Character, public Alive
{
    public:
        Enemy(const sf::Texture& texture);
        virtual ~Enemy();

        virtual void load(std::string filename);
        virtual void load(std::string filename, std::string fWeapon);
        virtual void goToCastle(sf::Time elapsedTime);
        virtual bool isNearToCastle() const;
        virtual void nearToCastle();
        virtual void attack(sf::Time elapsedTime);

        enum Type{BLINK}; // this is the basic animations for enemies
        void loadAnimationsFromNode(Node& root);

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);

    private:
        float _direction, _velocity;
        bool _nearToCastle;

        BarDisplay _healthBar;
};

#endif
