#include "config.hpp"
#include "game.hpp"
#include "context.hpp"
#include "tools/log.hpp"

#include "gamestate.hpp"

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
    Log::write(Log::LOG_INFO, "Playing Screen initialization");

    Context& c = Game::getContext();
    Level& lvl = Game::getContext().getLevel();

    std::string level("level1.xml");
    lvl.loadFromFile(LEVELS_PATH + level);
    Log::write(Log::LOG_INFO, std::string("Charging level " + level));

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
    app.draw(lvl.getGround());
    app.draw(lvl.getPlayer());
    for(std::list<Enemy*>::iterator itr = enemies.begin() ; itr != enemies.end() ; ++itr)
    {
        app.draw(**itr);
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
