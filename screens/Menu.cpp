#include "Menu.hpp"

#include <cassert>
#include <SFML/Window/Keyboard.hpp>

#include "../config.hpp"
#include "../tools/locator.hpp"

Menu::Menu(StateMachine& stateMachine) : _stateMachine(stateMachine),
                                         _playingScreen(new PlayingScreen(stateMachine)) // deleted in the state machine
{
    _stateMachine.add("playingscreen", _playingScreen);
    init();
}

Menu::~Menu()
{
}

void Menu::init()
{
    ImageManager* im = Locator::getImageManager();
    _texture = im->getTexture(IMAGES_PATH"menu.png");
    assert(_texture != NULL);

    _sprite.setTexture(*_texture, true);
}

void Menu::update(sf::Time elapsedTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
    {
        _playingScreen->load("level1.xml");
        _stateMachine.change("playingscreen");
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
    {
        _playingScreen->load("level2.xml");
        _stateMachine.change("playingscreen");
    }
}

void Menu::draw(sf::RenderWindow& app)
{
    app.draw(_sprite);
}

void Menu::onEnter()
{
}

void Menu::onExit()
{
}
