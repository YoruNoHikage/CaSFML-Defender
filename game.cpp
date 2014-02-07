#include <string>
#include "config.hpp"

#include "game.hpp"

#include "screens/statemachine.hpp"
#include "screens/splashscreen.hpp"
#include "gamestate.hpp"

Game::Game() : _isExiting(false)
{
}

Game::~Game()
{
}

void Game::start()
{
    // Initialize tools
    ImageManager *im = new ImageManager(); // deleted in the Locator destructor
    Locator::provideImageManager(im);

    Log::write(Log::LOG_INFO, "ImageManager loaded");

    sf::err().rdbuf(std::cout.rdbuf());

    Context &context = getContext();
    sf::RenderWindow &app = context.getApp();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    app.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Patate en frite", sf::Style::Default, settings);
    app.setView(sf::View(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT)));


    Log::write(Log::LOG_INFO, std::string("Window " + toString(WINDOW_WIDTH) + ";" + toString(WINDOW_HEIGHT)));
    Log::write(Log::LOG_INFO, std::string("View " + toString(VIEW_WIDTH) + ";" + toString(VIEW_HEIGHT)));

    std::srand(time(NULL));

    app.setVerticalSyncEnabled(true);

    // Initialize screens
    _stateMachine.add("splashscreen", new SplashScreen(_stateMachine));
    _stateMachine.add("playingscreen", new PlayingScreen(_stateMachine));

    _stateMachine.change("splashscreen");

    while(!_isExiting)
    {
        gameLoop();
    }

    app.close();
}

void Game::gameLoop()
{
    sf::RenderWindow& app = getContext().getApp();
    while(app.pollEvent(_currentEvent))
    {
        switch(_currentEvent.type)
        {
            case sf::Event::Closed:
                _isExiting = true;
                break;
            case sf::Event::KeyPressed:
                if(_currentEvent.key.code == sf::Keyboard::F3)
                    getContext().setDebug(!getContext().getDebug());
                break;
        }

    }
    sf::Time elapsed = _clock.restart();

    app.clear();

    _stateMachine.update(elapsed);
    _stateMachine.draw(app);

    app.display();
}

Context& Game::getContext()
{
    static Context* context = new Context();
    return *context;
}
