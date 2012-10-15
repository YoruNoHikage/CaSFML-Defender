#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "bullet.hpp"

class Weapon
{
    public:
        Weapon(sf::Texture &texture, sf::Texture &textureBullet);
        void throwBullet(int angle = 0);
        sf::Sprite getSprite();
        Bullet* getBullet();
        ~Weapon();

    private:
        sf::Sprite sprite;
        Bullet *bullet;
};


#endif

