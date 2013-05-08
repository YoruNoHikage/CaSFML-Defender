#include "config.hpp"

#include "game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::start()
{
    if(_gameState != Uninitialized)
        return;

    ImageManager *im = new ImageManager(); // deleted in the Locator destructor
    Locator::provideImageManager(im);

    Context &context = getContext();
    sf::RenderWindow &app = context.getApp();

    app.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Patate en frite");

    _gameState = Game::ShowingSplash;

    _castle.load("castle.png");
    if(_castle.isLoaded())
            _castle.setPosition(WINDOW_WIDTH - _castle.getDimension().width, WINDOW_HEIGHT - _castle.getDimension().height - 50);

    _player.load("character.png", "weapon.png");
    if(_player.isLoaded())
    {
        _player.setPosition(_castle.getPosition().x + 10,
                               _castle.getPosition().y - _player.getDimension().height * 3/4);
        Weapon *weapon = _player.getWeapon();
        if(weapon != NULL)
            weapon->setPosition(_player.getPosition().x, _player.getPosition().y + weapon->getDimension().height);
    }

    _ground.load("ground.png");
    if(_ground.isLoaded())
    {
        _ground.setPosition(0, WINDOW_HEIGHT - _ground.getDimension().height);
        if(_castle.isLoaded())
            _castle.setPosition(WINDOW_WIDTH - _castle.getDimension().width, WINDOW_HEIGHT - _castle.getDimension().height - _ground.getDimension().height / 2);
    }

    _background.load("background.png");
    _background.setPosition(0, 0);

    context.getShots().clear();
    context.getEnemies().clear();

    std::srand(time(NULL));

    app.setVerticalSyncEnabled(true);

    while(!isExiting())
    {
        gameLoop();
    }

    app.close();
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
    sf::RenderWindow& app = getContext().getApp();
    app.pollEvent(_currentEvent);
    switch(_gameState)
    {
        case Game::ShowingSplash:
            showSplashScreen();
            break;
        case Game::Playing:
            app.clear();

            updateAll();
            drawAll();

            app.display();

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
    splashscreen.show(getContext().getApp());
    _gameState = Game::Playing;
}

void Game::updateAll()
{
    sf::Time elapsed = _clock.restart();
    _background.update(elapsed);
    _ground.update(elapsed); // useless but...
    _player.update(elapsed);
    _castle.update(elapsed);

    std::list<Shot*> &shots = getContext().getShots();
    for(std::list<Shot*>::iterator itr = shots.begin() ; itr != shots.end() ; ++itr)
    {
        if((*itr)->hasToBeRemoved())
        {
            delete *itr;
            itr = shots.erase(itr);
        }
        else
            (*itr)->update(elapsed);
    }

    /** Updates enemies */
    std::list<Enemy*> &enemies = getContext().getEnemies();
    for(std::list<Enemy*>::iterator itr = enemies.begin() ; itr != enemies.end() ; ++itr)
    {
        if(!(*itr)->isAlive())
        {
            delete *itr;
            itr = enemies.erase(itr);
        }
        else
            (*itr)->update(elapsed);
    }
    _em.getNewEnemies(elapsed);

    checkAllCollisions();
}

void Game::checkAllCollisions()
{
    // collision between shots and enemies
    std::list<Shot*> &shots = getContext().getShots();
    std::list<Enemy*> &enemies = getContext().getEnemies();
    for(std::list<Shot*>::const_iterator itr = shots.begin() ; itr != shots.end() ; ++itr)
    {
        for(std::list<Enemy*>::iterator jtr = enemies.begin() ; jtr != enemies.end() ; ++jtr)
        {
            if((*itr)->collide(**jtr))
            {
                (*itr)->die();
                (*jtr)->die();
                break; // we break the loop to not kill others enemies
            }
        }

        if((*itr)->collide(_ground))
            (*itr)->die();
    }

    for(std::list<Enemy*>::iterator itr = enemies.begin() ; itr != enemies.end() ; ++itr)
    {
       if(!(*itr)->isNearToCastle())
        {
            // collision between enemies and the castle
            if((*itr)->collide(_castle))
            {
                (*itr)->nearToCastle();
            }
        }
    }
}

void Game::drawAll()
{
    sf::RenderWindow &app = getContext().getApp();
    std::list<Shot*> &shots = getContext().getShots();
    std::list<Enemy*> &enemies = getContext().getEnemies();

    _background.draw(app);
    _ground.draw(app);
    _player.draw(app);
    for(std::list<Enemy*>::iterator itr = enemies.begin() ; itr != enemies.end() ; ++itr)
    {
        (*itr)->draw(app);
    }
    _castle.draw(app);
    for(std::list<Shot*>::const_iterator itr = shots.begin() ; itr != shots.end() ; ++itr)
    {
        (*itr)->draw(app);
    }
}

Context& Game::getContext()
{
    static Context* context = new Context();
    return *context;
}
