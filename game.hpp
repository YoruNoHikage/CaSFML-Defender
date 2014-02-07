#ifndef GAME_HPP
#define GAME_HPP

#include "screens/statemachine.hpp"

/** \brief Encapsulates everything
 */
class Game
{
    public:
        Game();
        virtual ~Game();

        void start();

        static Context& getContext();

    private:
        void gameLoop();

        StateMachine _stateMachine;

        bool _isExiting;

        sf::Event _currentEvent;
        sf::Clock _clock;
};

#endif
