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

    c.getShots().clear();
    c.getCharacters().clear();
}

void PlayingScreen::load(std::string levelName)
{
    Level& lvl = Game::getContext().getLevel();

    std::string level(levelName);
    lvl.loadFromFile(LEVELS_PATH + level);
    Log::write(Log::LOG_INFO, std::string("Charging level " + level));
}

/** \brief Update the playing screen and call the collision function
 *
 * \param elapsedTime sf::Time
 * \return void
 *
 */
void PlayingScreen::update(sf::Time elapsedTime)
{
    if(Game::getContext().isGameOver())
        _stateMachine.change("gameover");

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

    /** Updates characters */
    std::list<Character*> &characters = Game::getContext().getCharacters();
    for(std::list<Character*>::iterator itr = characters.begin() ; itr != characters.end() ; ++itr)
    {
        if(!(*itr)->isAlive())
        {
            delete *itr;
            itr = characters.erase(itr);
        }
        else
            (*itr)->update(elapsedTime);
    }
    _cm.getNewCharacters(elapsedTime);

    checkAllCollisions();
}

/** \brief Check for the collisions between the objects
 *
 * \return void
 *
 */
void PlayingScreen::checkAllCollisions()
{
    // collision between shots and characters
    std::list<Shot*> &shots = Game::getContext().getShots();
    std::list<Character*> &characters = Game::getContext().getCharacters();
    for(std::list<Shot*>::const_iterator itr = shots.begin() ; itr != shots.end() ; ++itr)
    {
        for(std::list<Character*>::iterator jtr = characters.begin() ; jtr != characters.end() ; ++jtr)
        {
            if((*itr)->collide(**jtr))
            {
                (*itr)->die();
                (*jtr)->receiveDamages(1);
                break; // we break the loop to not kill others characters
            }
        }

        if((*itr)->collide(Game::getContext().getLevel().getGround()))
            (*itr)->die();
    }

    for(std::list<Character*>::iterator itr = characters.begin() ; itr != characters.end() ; ++itr)
    {
       if(!(*itr)->isNearToCastle())
        {
            // collision between characters and the castle
            Castle& castle(Game::getContext().getLevel().getCastle());
            if((*itr)->collide(castle))
            {
                (*itr)->nearToCastle(castle);
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
    std::list<Character*> &characters = c.getCharacters();

    app.draw(lvl.getBackground());
    app.draw(lvl.getGround());
    app.draw(lvl.getPlayer());
    for(std::list<Character*>::iterator itr = characters.begin() ; itr != characters.end() ; ++itr)
    {
        app.draw(**itr);
    }
    app.draw(lvl.getCastle());
    for(std::list<Shot*>::const_iterator itr = shots.begin() ; itr != shots.end() ; ++itr)
    {
        app.draw(**itr);
    }
}

/** \brief Launched when the playingscreen is loaded in the state machine
 *
 * \return void
 *
 */
void PlayingScreen::onEnter()
{
    Game::getContext().reset();
}

/** \brief Launched when the playingscreen is ended in the state machine
 *
 * \return void
 *
 */
void PlayingScreen::onExit()
{
}
