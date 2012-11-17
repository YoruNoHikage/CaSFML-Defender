#include "../config.hpp"

#include "../game.hpp"
#include "player.hpp"

Player::Player()
{
}

Player::~Player()
{
}

void Player::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);
    if(Game::getCurrentEvent().type == sf::Event::MouseButtonPressed)
    {
        if(Game::getCurrentEvent().mouseButton.button == sf::Mouse::Left)
            // if mouse button left is pressed, the character attacks
            attack(elapsedTime, sf::Vector2f(Game::getCurrentEvent().mouseButton.x, Game::getCurrentEvent().mouseButton.y));
    }

    getWeapon()->update(elapsedTime);
}

void Player::attack(sf::Time elapsedTime, sf::Vector2f location)
{
    getWeapon()->shoot(elapsedTime, location);
}
