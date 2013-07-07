#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "character.hpp"

class Enemy : public Character
{
    public:
        Enemy();
        virtual ~Enemy();

        virtual void load(std::string filename);
        virtual void load(std::string filename, std::string fWeapon);
        virtual void update(sf::Time elapsedTime);
        virtual void goToCastle(sf::Time elapsedTime);
        virtual bool isNearToCastle() const;
        virtual void nearToCastle();
        virtual void attack(sf::Time elapsedTime);
        virtual void die();

    private:
        float _direction, _velocity;
        bool _nearToCastle;
};

#endif
