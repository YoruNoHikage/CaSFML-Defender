#include "../config.hpp"

#include "../tools/rapidxml/rapidxml.hpp"
#include "../tools/rapidxml/rapidxml_utils.hpp"

#include "level.hpp"

Level::Level() : _name("<Unamed level>")
{
}

Level::~Level()
{
}

/** \brief Load the level's objects from a XML file with a proxy class
 *
 * \param filename const std::string&
 * \return void
 *
 * TO DO : Use the abstract class with a provider to set globally the parsing language
 */
#include "../tools/node.hpp" //debug
#include "../tools/xmlnode.hpp" //debug
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
        x = atoi(weaponNode.firstAttributeValue("x").c_str());
        y = atoi(weaponNode.firstAttributeValue("y").c_str());
        _castle.setPosition(x, y);
    }
    catch(std::exception const& e)
    {
        // Logger class please !
        std::cout << "Error : " << e.what() << std::endl;
    }
}
