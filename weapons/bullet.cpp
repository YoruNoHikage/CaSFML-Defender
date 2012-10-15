#include <iostream>
#include <SFML/Graphics.hpp>

#include "../config.hpp"
#include "bullet.hpp"

Bullet::Bullet(sf::Texture &texture)
{
    sprite.setTexture(texture);
    sprite.setScale(SCALE, SCALE);
}

void Bullet::move()
{
    sprite.move(50, 50);
}

sf::Sprite Bullet::getSprite()
{
    return sprite;
}
