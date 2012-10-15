#include <iostream>
#include <SFML/Graphics.hpp>

#include "../config.hpp"
#include "weapon.hpp"

Weapon::Weapon(sf::Texture &texture, sf::Texture &textureBullet)
{
    sprite.setTexture(texture);
    sprite.setScale(SCALE, SCALE);

    bullet = new Bullet(textureBullet);
}

void Weapon::throwBullet(int angle)
{
    //verify if there are bullets
    // add bullet to a vector
    bullet->move();
}

sf::Sprite Weapon::getSprite()
{
    return sprite;
}

Bullet* Weapon::getBullet()
{
    return bullet;
}

Weapon::~Weapon()
{
    delete bullet;
}
