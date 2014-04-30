#include <string>
#include <iostream>

#include "config.hpp"

#include "game.hpp"

#include "screens/splashscreen.hpp"
#include "gamestate.hpp"
#include "tools/imagemanager.hpp"
#include "tools/locator.hpp"
#include "tools/log.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game() : _stateMachine(),
               _isExiting(false),
               _currentEvent(),
               _clock(),
               _timeSinceLastUpdate(),
               _font(),
               _statisticsText(),
               _statisticsUpdateTime(),
               _statisticsNumFrames(0)
{
    _font.loadFromFile("data/sansation.ttf");
    _statisticsText.setFont(_font);
    _statisticsText.setPosition(5.f, 5.f);
    _statisticsText.setCharacterSize(20);
}

Game::~Game()
{
}

void Game::run()
{
    Log::write(Log::LOG_INFO, "== Starting Game ==");

    // Initialize tools
    ImageManager *im = new ImageManager(); // deleted in the Locator destructor
    Locator::provideImageManager(im);

    Log::write(Log::LOG_INFO, "ImageManager loaded");

    sf::err().rdbuf(std::cout.rdbuf());

    Context &context = getContext();
    sf::RenderWindow &app = context.getApp();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    Log::write(Log::LOG_INFO, "Antialiasing Level set to 8");

    sf::VideoMode videoMode;
    sf::Uint32 style = sf::Style::Fullscreen;

    if(style == sf::Style::Fullscreen)
        videoMode = sf::VideoMode::getDesktopMode();
    else
        videoMode = sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);

    app.create(videoMode, "CaSFML-Defender", style, settings); // for debug / screenshots / screencasts
    app.setPosition(sf::Vector2i(0, 0)); // for screenshots / screencasts
    app.setView(sf::View(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT)));
    Log::write(Log::LOG_INFO, std::string("Window " + toString(WINDOW_WIDTH) + ";" + toString(WINDOW_HEIGHT)));
    Log::write(Log::LOG_INFO, std::string("View " + toString(VIEW_WIDTH) + ";" + toString(VIEW_HEIGHT)));

    resizeViewport(videoMode.width, videoMode.height, app);

    std::srand(time(NULL));

    app.setVerticalSyncEnabled(true);

    // Initialize screens
    Log::write(Log::LOG_INFO, "Initialize screens");
    _stateMachine.add("splashscreen", new SplashScreen(_stateMachine));
    _stateMachine.add("playingscreen", new PlayingScreen(_stateMachine));

    _stateMachine.change("splashscreen");

    _timeSinceLastUpdate = sf::Time::Zero;
    while(!_isExiting)
    {
        gameLoop();
    }

    app.close();
}

void Game::gameLoop()
{
    sf::RenderWindow& app = getContext().getApp();

    sf::Time elapsedTime = _clock.restart();
    _timeSinceLastUpdate += elapsedTime;
    while(_timeSinceLastUpdate > Game::TimePerFrame)
    {
        _timeSinceLastUpdate -= Game::TimePerFrame;

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
                    else if(_currentEvent.key.code == sf::Keyboard::Escape)
                        _isExiting = true;
                    break;
                case sf::Event::Resized:
                    Log::write(Log::LOG_INFO, "Resized, new size : " + toString(_currentEvent.size.width) + ";"
                                                                     + toString(_currentEvent.size.height));

                    resizeViewport(_currentEvent.size.width, _currentEvent.size.height, app);
                    break;
            }

        }

        // Update every frame
        _stateMachine.update(Game::TimePerFrame);
    }

    if(getContext().getDebug())
        updateStats(elapsedTime);

    app.clear();

    _stateMachine.draw(app);
    if(getContext().getDebug())
        app.draw(_statisticsText);

    app.display();
}

void Game::updateStats(sf::Time elapsedTime)
{
    _statisticsUpdateTime += elapsedTime;
    _statisticsNumFrames += 1;

    	if(_statisticsUpdateTime >= sf::seconds(1.0f))
        {
            _statisticsText.setString("Frames / Second = " + toString(_statisticsNumFrames) + "\n" +
                                      "Time / Update = " + toString(_statisticsUpdateTime.asMicroseconds() / _statisticsNumFrames) + "us");

            _statisticsUpdateTime -= sf::seconds(1.0f);
            _statisticsNumFrames = 0;
        }
}

Context& Game::getContext()
{
    static Context* context = new Context();
    return *context;
}

void Game::resizeViewport(int width, int height, sf::RenderWindow& app)
{
    float ratio(static_cast<float>(VIEW_WIDTH) / VIEW_HEIGHT);
    sf::View view(app.getView());
    sf::FloatRect viewportSize;

    if(static_cast<float>(width) / height > ratio)
    {
        float padX((width - (height * ratio)) / 2);
        float relative(padX / width);

        viewportSize = sf::FloatRect(relative, 0.f, 1.f - relative * 2, 1.f);
        Log::write(Log::LOG_INFO, toString(viewportSize));
    }
    else if(static_cast<float>(_currentEvent.size.width) / _currentEvent.size.height < ratio)
    {
        float padY((height - (width / ratio)) / 2);
        float relative(padY / height);
        viewportSize = sf::FloatRect(0.f, relative, 1.f, 1.f - relative * 2);
    }
    else
         viewportSize = sf::FloatRect(0.f, 0.f, 1.f, 1.f);

    view.setViewport(viewportSize);
    app.setView(view);
}
