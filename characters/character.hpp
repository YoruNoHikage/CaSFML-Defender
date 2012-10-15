#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "../weapons/weapon.hpp"

class Character
{
    public:
        Character(sf::Texture &texture, sf::Texture &textureWeapon, sf::Texture &textureBullet);
        void attack(sf::Vector2i position);
        sf::Sprite getSprite();
        Weapon* getWeapon();
        int setPosition(float x, float y);
        ~Character();

    private:
        sf::Sprite sprite;
        Weapon *weapon;
};


#endif
