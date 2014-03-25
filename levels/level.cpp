#include "../config.hpp"

#include "level.hpp"
#include "../hitbox/boundingboxhitbox.hpp"
#include "../characters/knight.hpp"

/** \brief ctor
 */
Level::Level(sf::RenderWindow& app) : _app(app),
                                      _name("<Unamed level>"),
                                      _player(NULL)
{
}

/** \brief dtor
 */
Level::~Level()
{
    std::for_each(_waves.begin(), _waves.end(), Deallocator<Wave>());
    delete _player;
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

        buildLevel(root);

        // The waves
        Node& wavesNode = root.firstChild("waves");
        std::vector<Node*> waveNodes = wavesNode.getChildren("wave");
        Factory<Enemy>& enemyFactory = Factory<Enemy>::getFactory(); // Factory to know what type to build

        // Creation of each wave
        std::map<std::string, Node*> files; // used to avoid the reload of a single file
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
                    sf::Texture& texture = *(Locator::getImageManager()->getTexture(IMAGES_PATH + (*enemyItr)->firstAttributeValue("texture")));
                    Enemy* enemy = enemyFactory.build((*enemyItr)->firstAttributeValue("class"), texture);

                    // We load the animations corresponding to the class
                    std::string entityFilename = (*enemyItr)->firstAttributeValue("file");
                    std::map<std::string, Node*>::iterator fItr = files.find(entityFilename);
                    if(fItr == files.end()) // if the node doesn't exist already, we load it
                    {
                        Log::write(Log::LOG_INFO, "Loading entity file : " + entityFilename);
                        Node* entityNode = new XMLNode();
                        files.insert(std::make_pair(entityFilename, entityNode));
                        entityNode->loadFromFile(entityFilename);
                        enemy->loadAnimationsFromNode(*entityNode);
                    }
                    else
                        enemy->loadAnimationsFromNode(*fItr->second);

                    ///@todo: dynamic hitbox
                    enemy->setHitbox(new BoundingBoxHitbox(enemy->getGlobalBounds()));
                    Log::write(Log::LOG_INFO, "Enemy's hitbox creation : " + toString(enemy->getGlobalBounds()));
                    Log::write(Log::LOG_INFO, "Enemy's life : " + toString(enemy->getLife()));

                    // how to deal with positions ? In the file ?
                    enemy->setPosition(- enemy->getGlobalBounds().width,
                                       VIEW_HEIGHT - enemy->getGlobalBounds().height - _ground.getGlobalBounds().height / 2);

                    wave->addEnemy(enemy);
                }

                _waves.push_back(wave);
            }
            else
                delete wave;
        }

        // If the code above throws an exception, we're screwed...
        for(std::map<std::string, Node*>::iterator itr = files.begin() ; itr != files.end() ; ++itr)
            delete itr->second;
    }
    catch(std::exception const& e)
    {
        Log::write(Log::LOG_ERROR, "Error : " + toString(e.what()));
    }
}

void Level::buildLevel(Node& root)
{
    // The background
    _background.load(root.firstChild("background").firstAttributeValue("file"));
    _background.setPosition(0, 0);

    // The ground
    Node& groundNode = root.firstChild("ground");
    _ground.load(groundNode.firstAttributeValue("file"));

    int x = 0, y = 0;
    /*_ground.setPosition(x, y);*/

    // The player
    Node& playerNode = root.firstChild("player");

    sf::Texture* playerTexture = Locator::getImageManager()->getTexture(IMAGES_PATH + playerNode.firstAttributeValue("texture"));
    if(!playerTexture)
        throw std::runtime_error("Player's texture not found");
    _player = new Player(*playerTexture);

    XMLNode playerFile;
    playerFile.loadFromFile(playerNode.firstAttributeValue("file"));
    _player->loadFromNode(playerFile);

    const std::vector<Node*>& weaponsNode = playerNode.getChildren("weapon");
    for(std::size_t i = 0 ; i < weaponsNode.size() ; i++)
    {
        const std::string& filename = weaponsNode[i]->firstAttributeValue("file");

        Weapon* weapon = new Weapon();
        weapon->load(filename);
        ///@todo: loadWeaponFromNode
        _player->addWeaponToStack(weapon);
        Log::write(Log::LOG_INFO, "Loading new weapon " + filename);
    }

    x = y = 0;
    x = atoi(playerNode.firstAttributeValue("x").c_str());
    y = atoi(playerNode.firstAttributeValue("y").c_str());
    _player->setPosition(x, y);

    // The castle
    Node& castleNode = root.firstChild("castle");
    _castle.load(castleNode.firstAttributeValue("file"));

    int offsetX = 0, offsetY = 0;
    try
    {
        std::string offsetXStr = castleNode.firstAttributeValue("offsetx");
        offsetX = offsetXStr != "" ? atoi(offsetXStr.c_str()) : 0;
    }
    catch(std::runtime_error& e)
    { /* if offsetX are not there, it's not a problem */ }

    try
    {
        std::string offsetYStr = castleNode.firstAttributeValue("offsety");
        offsetY = offsetYStr != "" ? atoi(offsetYStr.c_str()) : 0;
    }
    catch(std::runtime_error& e)
    { /* if offsetY are not there, it's not a problem */ }

    std::string position = castleNode.firstAttributeValue("position");
    if(position == "left")
        x = std::abs(offsetX);
    else if(position == "middle")
        x = VIEW_WIDTH / 2 - _castle.getGlobalBounds().width / 2 + offsetX;
    else // by default it's right
        x = VIEW_WIDTH - _castle.getGlobalBounds().width - std::abs(offsetX);

    y = VIEW_HEIGHT - _castle.getGlobalBounds().height - std::abs(offsetY);
    _castle.setPosition(x, y);
    _castle.getHitbox()->setPosition(x, y);
    Log::write(Log::LOG_INFO, std::string("Loading castle to the " + position + " : offsets : " + toString(offsetX) + ";" + toString(offsetX)
                                          + " - position " + toString(_castle.getPosition()) + toString(_castle.getGlobalBounds())));
    Log::write(Log::LOG_INFO, std::string("Castle sprite hitbox : position " + toString(_castle.getHitbox()->getPosition())
                                          + toString(_castle.getGlobalBounds())));
}

Wave* Level::getNextWave()
{
    if(_waves.empty())
        return NULL;

    Wave* response = _waves.front();
    _waves.erase(_waves.begin());

    return response;
}
