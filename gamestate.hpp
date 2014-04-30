#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "screens/statemachine.hpp"
#include "characters/player.hpp"
#include "characters/CharacterManager.hpp"
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
        void load(std::string levelName);

        void update(sf::Time elapsedTime);
        void checkAllCollisions();
        void draw(sf::RenderWindow& app);
        void onEnter();
        void onExit();

    private:
        StateMachine& _stateMachine;

        CharacterManager _cm;
};

#endif // GAMESTATE_HPP
