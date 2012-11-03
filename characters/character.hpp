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
        virtual void update(sf::Time elapsedTime);
        virtual void draw(sf::RenderWindow& window);

        void attack(sf::Time elapsedTime, sf::Vector2i location);

    private:
        Weapon _weapon; // change later into a pointer with a weaponManager
};

#endif
