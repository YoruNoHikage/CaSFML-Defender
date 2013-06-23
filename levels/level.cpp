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

/** \brief Load the level's objects from a XML file
 *
 * \param filename const std::string&
 * \return void
 *
 * REFACTORING TO DO : This code is ugly (redundant), make a class to avoid this
 */
void Level::loadFromFile(const std::string& filename)
{
    try
    {
        rapidxml::file<> file(filename.c_str());
        rapidxml::xml_document<> document;
        document.parse<0>(file.data());

        // The first node has to be "level"
        rapidxml::xml_node<>* xmlLevel = document.first_node("level");
        if(!xmlLevel)
        {
            std::string error = "Error " + filename + " : first node has to be \"level\"";
            throw std::runtime_error(error);
        }

        // We fill the level's attributes

        // Firstly, the name
        if(xmlLevel->first_node("name") != NULL)
            _name = xmlLevel->first_node("name")->name();

        // Then the background
        if(xmlLevel->first_node("background") != NULL)
        {
            rapidxml::xml_node<>* node = xmlLevel->first_node("background");

            if(node->first_attribute("file") != NULL)
                _background.load(node->first_attribute("file")->value());
            _background.setPosition(0, 0);
        }
        else
            throw std::runtime_error(std::string("No background defined in ") + filename);

        // The ground
        if(xmlLevel->first_node("ground") != NULL)
        {
            rapidxml::xml_node<>* node = xmlLevel->first_node("ground");

            if(node->first_attribute("file") != NULL)
                _ground.load(node->first_attribute("file")->value());

            int x = 0, y = 0;
            if(node->first_attribute("x") != NULL)
                x = atoi(node->first_attribute("x")->value());
            if(node->first_attribute("y") != NULL)
                y = atoi(node->first_attribute("y")->value());

            _ground.setPosition(x, y);
        }
        else
            throw std::runtime_error(std::string("No ground defined in ") + filename);

        // The player
        if(xmlLevel->first_node("player") != NULL)
        {
            rapidxml::xml_node<>* node = xmlLevel->first_node("player");

            // The weapons TO DO
            if(node->first_attribute("file") != NULL && node->first_node("weapon") != NULL)
            {
                rapidxml::xml_node<>* weaponNode = node->first_node("weapon");

                // OMG, kill me for that
                _player.load(node->first_attribute("file")->value(), weaponNode->first_attribute("file")->value());

                int x = 0, y = 0;
                if(node->first_attribute("x") != NULL)
                    x = atoi(weaponNode->first_attribute("x")->value());
                if(node->first_attribute("y") != NULL)
                    y = atoi(weaponNode->first_attribute("y")->value());

                _player.getWeapon()->setPosition(x, y);
            }
            else if(node->first_attribute("file") != NULL)
                _player.load(node->first_attribute("file")->value());
            else
                throw std::runtime_error(std::string("What am I supposed to say... the code here is ugly"));

            int x = 0, y = 0;
            if(node->first_attribute("x") != NULL)
                x = atoi(node->first_attribute("x")->value());
            if(node->first_attribute("y") != NULL)
                y = atoi(node->first_attribute("y")->value());

            _player.setPosition(x, y);
        }
        else
            throw std::runtime_error(std::string("No player defined in ") + filename);

        // The castle
        if(xmlLevel->first_node("castle") != NULL)
        {
            rapidxml::xml_node<>* node = xmlLevel->first_node("castle");

            if(node->first_attribute("file") != NULL)
                _castle.load(node->first_attribute("file")->value());

            int x = 0, y = 0;
            if(node->first_attribute("x") != NULL)
                x = atoi(node->first_attribute("x")->value());
            if(node->first_attribute("y") != NULL)
                y = atoi(node->first_attribute("y")->value());

            _castle.setPosition(x, y);
        }
        else
            throw std::runtime_error(std::string("No castle defined in ") + filename);
    }
    catch(std::exception const& e)
    {
        // Logger class please !
        std::cerr << "Error : " << e.what() << std::endl;
    }
}
