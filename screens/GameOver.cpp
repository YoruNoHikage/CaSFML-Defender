#include "GameOver.hpp"

#include <cassert>
#include <SFML/Window/Keyboard.hpp>

#include "../config.hpp"
#include "../tools/locator.hpp"

GameOver::GameOver(StateMachine& stateMachine) : _stateMachine(stateMachine)
{
    init();
}

GameOver::~GameOver()
{
}

void GameOver::init()
{
    ImageManager* im = Locator::getImageManager();
    _texture = im->getTexture(IMAGES_PATH"gameover.png");
    assert(_texture != NULL);

    _sprite.setTexture(*_texture);
}

void GameOver::update(sf::Time elapsedTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        _stateMachine.change("playingscreen");
}

void GameOver::draw(sf::RenderWindow& app)
{
    app.draw(_sprite);
}

void GameOver::onEnter()
{
}

void GameOver::onExit()
{
}
