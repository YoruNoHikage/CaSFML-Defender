#include "config.hpp"

#include "game.hpp"
#include "splashscreen/splashscreen.hpp"
#include "characters/character.hpp"
#include "landscape/background.hpp"

void Game::start()
{
    if(_gameState != Uninitialized)
        return;

    _mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Patate en frite");

    _gameState = Game::ShowingSplash;

    Character *character = new Character();

    _gameObjectManager.add("Character", character);

    Background *background = new Background();
    background->load(IMAGES_PATH"background.png");
    background->setPosition(0, 0);

    _gameObjectManager.add("Background", background);

    VisibleGameObject *ground = new VisibleGameObject(); // maybe change to another object who inherit from visiblegameobject
    ground->load(IMAGES_PATH"ground.png");
    if(ground->isLoaded())
        ground->setPosition(0, WINDOW_HEIGHT - 100); // change that into the constructor

    _gameObjectManager.add("Ground", ground);

    std::srand(time(NULL));

    while(!isExiting())
    {
        gameLoop();
    }

    _mainWindow.close();
}

bool Game::isExiting()
{
    if(_gameState == Game::Exiting)
        return true;
    else
        return false;
}

void Game::gameLoop()
{
    _mainWindow.pollEvent(_currentEvent);
    switch(_gameState)
    {
        case Game::ShowingSplash:
            showSplashScreen();
            break;
        case Game::Playing:
            _mainWindow.clear();

            sf::Time elapsed = _clock.restart();
            _gameObjectManager.updateAll(elapsed);
            _gameObjectManager.drawAll(_mainWindow);

            _mainWindow.display();

            if(_currentEvent.type == sf::Event::Closed)
            {
                _gameState = Game::Exiting;
            }
            break;
    }
}

void Game::showSplashScreen()
{
    SplashScreen splashscreen;
    splashscreen.show(_mainWindow);
    _gameState = Game::Playing;
}

sf::RenderWindow& Game::getWindow()
{
    return _mainWindow;
}

const sf::Event& Game::getCurrentEvent()
{
    return _currentEvent;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
sf::Event Game::_currentEvent;
sf::Clock Game::_clock;

GameObjectManager Game::_gameObjectManager;
