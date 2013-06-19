#include "config.hpp"

#include "game.hpp"

#include "screens/statemachine.hpp"
#include "screens/splashscreen.hpp"

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

    Context &context = getContext();
    sf::RenderWindow &app = context.getApp();

    app.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Patate en frite");

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

// Playing Screen

/** \brief ctor
 *
 * \param stateMachine StateMachine&
 *
 */
PlayingScreen::PlayingScreen(StateMachine& stateMachine) : _stateMachine(stateMachine)
{
    init();
}

/** \brief dtor
 */
PlayingScreen::~PlayingScreen()
{
}

/** \brief Initialize the textures and sprites' games
 *
 * \return void
 *
 */
void PlayingScreen::init()
{
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

    Game::getContext().getShots().clear();
    Game::getContext().getEnemies().clear();
}

/** \brief Update the playing screen and call the collision function
 *
 * \param elapsedTime sf::Time
 * \return void
 *
 */
void PlayingScreen::update(sf::Time elapsedTime)
{
    _background.update(elapsedTime);
    _ground.update(elapsedTime); // useless but...
    _player.update(elapsedTime);
    _castle.update(elapsedTime);

    std::list<Shot*> &shots = Game::getContext().getShots();
    for(std::list<Shot*>::iterator itr = shots.begin() ; itr != shots.end() ; ++itr)
    {
        if((*itr)->hasToBeRemoved())
        {
            delete *itr;
            itr = shots.erase(itr);
        }
        else
            (*itr)->update(elapsedTime);
    }

    /** Updates enemies */
    std::list<Enemy*> &enemies = Game::getContext().getEnemies();
    for(std::list<Enemy*>::iterator itr = enemies.begin() ; itr != enemies.end() ; ++itr)
    {
        if(!(*itr)->isAlive())
        {
            delete *itr;
            itr = enemies.erase(itr);
        }
        else
            (*itr)->update(elapsedTime);
    }
    _em.getNewEnemies(elapsedTime);

    checkAllCollisions();
}

/** \brief Check for the collisions between the objects
 *
 * \return void
 *
 */
void PlayingScreen::checkAllCollisions()
{
    // collision between shots and enemies
    std::list<Shot*> &shots = Game::getContext().getShots();
    std::list<Enemy*> &enemies = Game::getContext().getEnemies();
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


/** \brief Draw the game's objects
 *
 * \param app sf::RenderWindow&
 * \return void
 *
 */
void PlayingScreen::draw(sf::RenderWindow& app)
{
    std::list<Shot*> &shots = Game::getContext().getShots();
    std::list<Enemy*> &enemies = Game::getContext().getEnemies();

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

/** \brief Launched when the playingscreen is loaded in the state machine
 *
 * \return void
 *
 */
void PlayingScreen::onEnter()
{
}

/** \brief Launched when the playingscreen is ended in the state machine
 *
 * \return void
 *
 */
void PlayingScreen::onExit()
{
}
