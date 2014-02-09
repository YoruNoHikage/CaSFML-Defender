#include "../config.hpp"

#include "../game.hpp"
#include "player.hpp"

Player::Player(const sf::Texture& texture) : Character(texture)
{
}

Player::~Player()
{
}

void Player::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        // if mouse button left is pressed, the character attacks
        // TO DO : choosing between float or int dammit !
        attack(elapsedTime, Game::getContext().getApp().mapPixelToCoords(sf::Mouse::getPosition(Game::getContext().getApp())));

    getWeapon()->update(elapsedTime);
}

void Player::attack(sf::Time elapsedTime, sf::Vector2f location)
{
    getWeapon()->shoot(elapsedTime, location);
}
