#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "characters/enemy.hpp"
#include "weapons/shot.hpp"
#include "levels/level.hpp"

class Context {
    public:
        Context();
        ~Context();
        sf::RenderWindow& getApp() { return _mainWindow;};

        void reset();

        std::list<Shot*>& getShots();
        std::list<Character*>& getCharacters();

        void addShot(Shot* shot);
        void addCharacter(Character* character);

        Level& getLevel() { return _level; };

        bool getDebug() { return _isDebug; };
        void setDebug(bool debug) { _isDebug = debug; };

        void friendSaved() {}; ///@todo: stats

        bool isGameOver() { return _isGameOver; };
        bool isSuccess() { return _isSuccess; };
        void gameOver(bool success) { _isGameOver = true; _isSuccess = success; }; // game is finished, with success or not

    private:
        sf::RenderWindow _mainWindow;
        std::list<Shot*> _shots;
        std::list<Character*> _characters; // characters in game

        Level _level;

        bool _isDebug,
             _isGameOver,
             _isSuccess;
};

#endif
