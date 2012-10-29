#include "../config.hpp"

#include "character.hpp"

Character::Character()
{
    load(IMAGES_PATH"character.png");
    assert(isLoaded());
    getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
    getSprite().setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

Character::~Character()
{
}

// implements these methods in a mother class to inherit here and with enemies

void Character::load(std::string filename)
{
    VisibleGameObject::load(filename);
    _weapon.load(IMAGES_PATH"weapon.png");
}

void Character::update(sf::Time elapsedTime)
{
    VisibleGameObject::update(elapsedTime);
    _weapon.update(elapsedTime);
}

void Character::draw(sf::RenderWindow& window)
{
    VisibleGameObject::draw(window);
    _weapon.draw(window);
}
