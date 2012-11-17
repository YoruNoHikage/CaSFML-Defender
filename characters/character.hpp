#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "../visiblegameobject.hpp"
#include "../weapons/weapon.hpp"

class Character : public VisibleGameObject
{
    public:
        Character();
        virtual ~Character();

        virtual void load(std::string filename);
        virtual void load(std::string filename, std::string fWeapon);
        virtual void update(sf::Time elapsedTime);
        virtual void draw(sf::RenderWindow& window);
        virtual void attack(sf::Time elapsedTime);

        virtual Weapon* getWeapon();

    private:
        Weapon *_weapon; // player can change it and enemies can lose it
};

#endif
