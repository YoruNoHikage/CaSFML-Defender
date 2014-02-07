#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "screens/statemachine.hpp"
#include "characters/player.hpp"
#include "characters/enemymanager.hpp"
#include "landscape/background.hpp"
#include "landscape/ground.hpp"
#include "castle.hpp"

/** \brief Represents the playing screen
 */
class PlayingScreen : public IState
{
    public:
        PlayingScreen(StateMachine& stateMachine);
        ~PlayingScreen();

        void init();
        void update(sf::Time elapsedTime);
        void checkAllCollisions();
        void draw(sf::RenderWindow& app);
        void onEnter();
        void onExit();

    private:
        StateMachine& _stateMachine;

        EnemyManager _em;
};

#endif // GAMESTATE_HPP
