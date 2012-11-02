#include "config.hpp"

#include "game.hpp"

void Game::start()
{
    if(_gameState != Uninitialized)
        return;

    _mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Patate en frite");

    _gameState = Game::ShowingSplash;

    _ground.load(IMAGES_PATH"ground.png");
    if(_ground.isLoaded())
        _ground.setPosition(0, WINDOW_HEIGHT - 100); // change that into the constructor

    _background.load(IMAGES_PATH"background.png");
    _background.setPosition(0, 0);

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

            updateAll();
            drawAll();

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

void Game::updateAll()
{
    sf::Time elapsed = _clock.restart();
    _background.update(elapsed);
    _ground.update(elapsed); // useless but...
    _castle.update(elapsed);
    _character.update(elapsed);
}

void Game::drawAll()
{
    _background.draw(_mainWindow);
    _ground.draw(_mainWindow);
    _castle.draw(_mainWindow);
    _character.draw(_mainWindow);
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

Character Game::_character;
Castle Game::_castle;
VisibleGameObject Game::_ground;
Background Game::_background;
