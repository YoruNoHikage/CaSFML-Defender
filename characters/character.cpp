#include <iostream>
#include <SFML/Graphics.hpp>

#include "../config.hpp"
#include "../weapons/weapon.hpp"
#include "character.hpp"

Character::Character(sf::Texture &texture, sf::Texture &textureWeapon, sf::Texture &textureBullet)
{
    sprite.setTexture(texture);
    sprite.setScale(SCALE, SCALE);

    weapon = new Weapon(textureWeapon, textureBullet);
}

void Character::attack(sf::Vector2i position)
{
    std::cout << "A l'attaque" << std::endl;
    // angle with position of the mouse
    weapon->throwBullet(/*angle*/);
}

sf::Sprite Character::getSprite()
{
    return sprite;
}

Weapon* Character::getWeapon()
{
    return weapon;
}

int Character::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

Character::~Character()
{
    delete weapon;
}
