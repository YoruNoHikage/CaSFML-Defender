#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "statemachine.hpp"
#include "../gamestate.hpp"

class Menu : public IState
{
    public:
        Menu(StateMachine& stateMachine);
        ~Menu();

        void init();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow& app);
        void onEnter();
        void onExit();

    private:
        sf::Texture *_texture;
        sf::Sprite _sprite;
        StateMachine& _stateMachine;

        PlayingScreen* _playingScreen;
};

#endif
