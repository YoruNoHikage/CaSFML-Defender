#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP

#include "statemachine.hpp"

class SplashScreen : IState
{
    public:
        SplashScreen();
        ~SplashScreen();

        void show(sf::RenderWindow& window); // DELETE

        void init();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow& app);
        void onEnter();
        void onExit();

    private:
        sf::Texture _splashTexture;
        sf::Sprite _splash;
};

#endif
