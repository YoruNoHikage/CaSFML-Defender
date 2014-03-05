#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "DrawableEntity.hpp"
#include "../Collidable.hpp"
#include "../visiblegameobject.hpp"
#include "../weapons/weapon.hpp"

class Character : public DrawableEntity, public Collidable
{
    public:
        Character(const sf::Texture& texture);
        virtual ~Character();

        virtual void load(std::string filename);
        virtual void load(std::string filename, std::string fWeapon);
        virtual void attack(sf::Time elapsedTime);

        virtual Weapon* getWeapon();

        bool isAlive();

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:

        bool _isAlive;
        Weapon *_weapon; // player can change it and enemies can lose it
};

#endif
