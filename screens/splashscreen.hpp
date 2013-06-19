#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP

#include "statemachine.hpp"

class SplashScreen : public IState
{
    public:
        SplashScreen(StateMachine& stateMachine);
        ~SplashScreen();

        void init();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow& app);
        void onEnter();
        void onExit();

    private:
        sf::Texture *_splashTexture;
        sf::Sprite _splash;
        StateMachine& _stateMachine;
};

#endif
