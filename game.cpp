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
    Context& c = Game::getContext();
    Level& lvl = Game::getContext().getLevel();

    lvl.loadFromFile(LEVELS_PATH"level1.xml");

    c.getShots().clear();
    c.getEnemies().clear();
}

/** \brief Update the playing screen and call the collision function
 *
 * \param elapsedTime sf::Time
 * \return void
 *
 */
void PlayingScreen::update(sf::Time elapsedTime)
{
    Level& lvl = Game::getContext().getLevel();

    lvl.getPlayer().update(elapsedTime);
    lvl.getBackground().update(elapsedTime);
    lvl.getCastle().update(elapsedTime);
    lvl.getGround().update(elapsedTime);

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

        if((*itr)->collide(Game::getContext().getLevel().getGround()))
            (*itr)->die();
    }

    for(std::list<Enemy*>::iterator itr = enemies.begin() ; itr != enemies.end() ; ++itr)
    {
       if(!(*itr)->isNearToCastle())
        {
            // collision between enemies and the castle
            if((*itr)->collide(Game::getContext().getLevel().getCastle()))
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
    Context& c = Game::getContext();
    Level& lvl = c.getLevel();

    std::list<Shot*> &shots = c.getShots();
    std::list<Enemy*> &enemies = c.getEnemies();

    lvl.getBackground().draw(app);
    lvl.getGround().draw(app);
    lvl.getPlayer().draw(app);
    for(std::list<Enemy*>::iterator itr = enemies.begin() ; itr != enemies.end() ; ++itr)
    {
        (*itr)->draw(app);
    }
    lvl.getCastle().draw(app);
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
