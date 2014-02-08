#ifndef GAME_HPP
#define GAME_HPP

#include "screens/statemachine.hpp"

/** \brief Encapsulates everything
 */
class Game : public sf::NonCopyable
{
    public:
        Game();
        ~Game();

        /** \brief Runs the game application
         *
         * \return void
         *
         */
        void run();

        ///@todo: removes this because global access is bad
        /** \brief Get the Context class
         *
         * \return Context&
         *
         */
        static Context& getContext();

    private:
        /** \brief Loops to update the game
         *
         * \return void
         *
         */
        void gameLoop();

        /** \brief Updates statistics to show the FPS
         *
         * \return void
         *
         */
        void updateStats(sf::Time elapsedTime);

        StateMachine _stateMachine;

        bool _isExiting;

        static const sf::Time TimePerFrame;
        sf::Event _currentEvent;
        sf::Clock _clock;
        sf::Time _timeSinceLastUpdate;

        sf::Font _font;
        sf::Text _statisticsText;
        sf::Time _statisticsUpdateTime;
        std::size_t	_statisticsNumFrames;
};

#endif
