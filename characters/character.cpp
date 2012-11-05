#include "../config.hpp"

#include "../game.hpp"
#include "character.hpp"

Character::Character()
{
}

Character::~Character()
{
}

// implements these methods in a mother class to inherit here and with enemies

void Character::load(std::string filename)
{
    VisibleGameObject::load(filename);
    assert(isLoaded());
    _weapon.load(IMAGES_PATH"weapon.png");
}

void Character::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);

    if(Game::getCurrentEvent().type == sf::Event::MouseButtonPressed)
    {
        if(Game::getCurrentEvent().mouseButton.button == sf::Mouse::Left)
            // if mouse button left is pressed, the character attacks
            attack(elapsedTime, sf::Vector2i(Game::getCurrentEvent().mouseButton.x, Game::getCurrentEvent().mouseButton.y));
    }

    _weapon.update(elapsedTime);
}

void Character::attack(sf::Time elapsedTime, sf::Vector2i location)
{
    _weapon.shoot(elapsedTime, location);
}

void Character::draw(sf::RenderWindow& window)
{
    VisibleGameObject::draw(window);
    _weapon.draw(window);
}

Weapon* Character::getWeapon()
{
    return &_weapon;
}
