#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "character.hpp"

class Enemy : public Character
{
    public:
        Enemy();
        ~Enemy();

        void load(std::string filename);
        void load(std::string filename, std::string fWeapon);
        void update(sf::Time elapsedTime);
        void goToCastle(sf::Time elapsedTime);
        bool isNearToCastle() const;
        void nearToCastle();
        void attack(sf::Time elapsedTime);
        void die();

    private:
        float _direction, _velocity;
        bool _nearToCastle;
};

#endif
