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

        std::list<Shot*>& getShots();
        std::list<Character*>& getCharacters();

        void addShot(Shot* shot);
        void addCharacter(Character* character);

        Level& getLevel() { return _level; };

        bool getDebug();
        void setDebug(bool debug);

    private:
        sf::RenderWindow _mainWindow;
        std::list<Shot*> _shots;
        std::list<Character*> _characters; // characters in game
        Level _level;

        bool _isDebug;
};

#endif
