#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "DrawableEntity.hpp"
#include "../Collidable.hpp"
#include "../Alive.hpp"
#include "../weapons/weapon.hpp"

#include "../castle.hpp"

class Character : public DrawableEntity, public Collidable, public Alive
{
    public:
        Character(const sf::Texture& texture);
        virtual ~Character();

        virtual void load(std::string filename, std::string fWeapon);

        virtual Weapon* getWeapon();

        virtual bool isNearToCastle() const;
        virtual void nearToCastle(Castle& castle);

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void goToCastle(sf::Time elapsedTime);

    protected:

        Weapon *_weapon; // player can change it and enemies can lose it

        float _direction, _velocity;

        bool _nearToCastle;
};

#endif
