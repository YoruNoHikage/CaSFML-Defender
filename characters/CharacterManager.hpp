#ifndef CHARACTERMANAGER_HPP
#define CHARACTERMANAGER_HPP

#include <list>

#include "character.hpp"

class CharacterManager
{
    public:
        CharacterManager();
        ~CharacterManager();

        void reset();

        void generateCharacters(); // for survival mode
        void getNewCharacters(sf::Time elapsedTime);

        bool isAnybodyStillAlive();

    private:
        std::list<Character*> _characters; // waiting to be added in the game
        sf::Time _generationTime, _elapsedTime;
        bool _waveOver, _hasMoreWaves;
};

#endif
