#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "../characters/player.hpp"
#include "../characters/CharacterManager.hpp"
#include "../landscape/background.hpp"
#include "../landscape/ground.hpp"
#include "../castle.hpp"
#include "wave.hpp"
#include "../tools/factory.hpp"
#include "../tools/xmlnode.hpp"

class Level
{
    public:
        Level(sf::RenderWindow& app);
        ~Level();

        void loadFromFile(const std::string& filename);

        Player& getPlayer() { return *_player; };
        Background& getBackground() { return _background; };
        Castle& getCastle() { return *_castle; };
        Ground& getGround() { return _ground; };

        Wave* getNextWave();

    private:
        Enemy* createEnemyFromNode(Node& enemyNode, Factory<Enemy>& enemyFactory, std::map<std::string, Node*>& files);

        void buildLevel(Node& root);

        void loadEntityFromFile(DrawableEntity& entity, std::string entityFilename, std::map<std::string, Node*>& files);

        sf::RenderWindow& _app;

        std::string _name; // level's name

        Player* _player;
        Background _background;
        Castle* _castle;
        Ground _ground;

        std::vector<Wave*> _waves;
};

#endif // LEVEL_HPP
