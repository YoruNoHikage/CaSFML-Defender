#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "../characters/player.hpp"
#include "../characters/enemymanager.hpp"
#include "../landscape/background.hpp"
#include "../landscape/ground.hpp"
#include "../castle.hpp"
#include "wave.hpp"

class Level
{
    public:
        Level();
        ~Level();

        void loadFromFile(const std::string& filename);

        Player& getPlayer() { return _player; };
        Background& getBackground() { return _background; };
        Castle& getCastle() { return _castle; };
        Ground& getGround() { return _ground; };

        Wave* getNextWave();

    private:
        std::string _name; // level's name

        Player _player;
        Background _background;
        Castle _castle;
        Ground _ground;

        std::vector<Wave*> _waves;
};

#endif // LEVEL_HPP
