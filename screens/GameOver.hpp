#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "statemachine.hpp"

class GameOver : public IState
{
    public:
        GameOver(StateMachine& stateMachine);
        ~GameOver();

        void init();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow& app);
        void onEnter();
        void onExit();

    private:
        sf::Texture *_texture;
        sf::Sprite _sprite;
        StateMachine& _stateMachine;
};

#endif
