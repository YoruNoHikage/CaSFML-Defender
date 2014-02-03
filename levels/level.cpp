#include "../config.hpp"

#include "level.hpp"
#include "../tools/factory.hpp"
#include "../tools/xmlnode.hpp"

/** \brief ctor
 */
Level::Level() : _name("<Unamed level>")
{
}

/** \brief dtor
 */
Level::~Level()
{
    std::for_each(_waves.begin(), _waves.end(), Deallocator<Wave>());
}

/** \brief Load the level's objects from a XML file with a proxy class
 *
 * \param filename const std::string&
 * \return void
 *
 * TO DO : Use the abstract class with a provider to set globally the parsing language
 */
void Level::loadFromFile(const std::string& filename)
{
    try
    {
        XMLNode root; // change the way to initialize the root node
        root.loadFromFile(filename);

        // The first node has to be "level"
        if(root.getName() != "level")
        {
            std::string error = "Error " + filename + " : first node has to be \"level\"";
            throw std::runtime_error(error);
        }

        // We fill the level's attributes

        // Firstly, the name
        _name = root.firstAttributeValue("name");

        // Then the background
        _background.load(root.firstChild("background").firstAttributeValue("file"));
        _background.setPosition(0, 0);

        // The ground
        Node& groundNode = root.firstChild("ground");
        _ground.load(groundNode.firstAttributeValue("file"));

        int x = 0, y = 0;
        x = atoi(groundNode.firstAttributeValue("x").c_str());
        y = atoi(groundNode.firstAttributeValue("y").c_str());
        _ground.setPosition(x, y);

        // The player
        Node& playerNode = root.firstChild("player");
        Node& weaponNode = playerNode.firstChild("weapon"); // multiple weapons please
        _player.load(playerNode.firstAttributeValue("file"), weaponNode.firstAttributeValue("file"));

        // Better if the weapon is set in the player ?
        x = y = 0;
        x = atoi(weaponNode.firstAttributeValue("x").c_str());
        y = atoi(weaponNode.firstAttributeValue("y").c_str());
        _player.getWeapon()->setPosition(x, y);

        x = y = 0;
        x = atoi(playerNode.firstAttributeValue("x").c_str());
        y = atoi(playerNode.firstAttributeValue("y").c_str());
        _player.setPosition(x, y);

        // The castle
        Node& castleNode = root.firstChild("castle");
        _castle.load(castleNode.firstAttributeValue("file"));

        x = y = 0;
        x = atoi(castleNode.firstAttributeValue("x").c_str());
        y = atoi(castleNode.firstAttributeValue("y").c_str());
        _castle.setPosition(x, y);

        // The waves
        Node& wavesNode = root.firstChild("waves");
        std::vector<Node*> waveNodes = wavesNode.getChildren("wave");
        Factory<Enemy>& enemyFactory = Factory<Enemy>::GetFactory(); // Factory to know what type to build

        // Creation of each wave
        for(std::vector<Node*>::iterator waveItr = waveNodes.begin() ; waveItr != waveNodes.end() ; ++waveItr)
        {
            // New enemies' wave !
            Wave* wave = new Wave();

            std::vector<Node*> enemyNodes = (*waveItr)->getChildren("enemy");
            // if empty, there is no wave
            if(!enemyNodes.empty())
            {
                // Fills with enemies !
                for(std::vector<Node*>::iterator enemyItr = enemyNodes.begin() ; enemyItr != enemyNodes.end() ; ++enemyItr)
                {
                    // Asks the factory for an instance of the asking class in the XML
                    Enemy* enemy = enemyFactory.build((*enemyItr)->firstAttributeValue("class"));

                    enemy->load((*enemyItr)->firstAttributeValue("file"));
                    // how to deal with positions ? In the file ?
                    enemy->setPosition(- enemy->getDimension().height, VIEW_HEIGHT - enemy->getDimension().height - 25);

                    wave->addEnemy(enemy);
                }

                _waves.push_back(wave);
            }
            else
                delete wave;
        }
    }
    catch(std::exception const& e)
    {
        // Logger class please !
        std::cout << "Error : " << e.what() << std::endl;
    }
}

Wave* Level::getNextWave()
{
    if(_waves.empty())
        return NULL;

    Wave* response = _waves.front();
    _waves.erase(_waves.begin());

    return response;
}
