#include "../config.hpp"

#include "imagemanager.hpp"

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
    std::map<std::string, sf::Texture*>::iterator it;
    for(it = _textures.begin(); it != _textures.end(); it++)
    {
        delete it->second;
    }
}

bool ImageManager::searchTexture(const std::string &textureLink, sf::Texture* &textureTemp)
{
    std::map<std::string, sf::Texture*>::iterator it;

    it = _textures.find(textureLink);

    if(it == _textures.end())
        return false;
    else
        textureTemp = it->second;

    return true;
}

sf::Texture* ImageManager::createTexture(const std::string &textureLink)
{
    sf::Texture *textureTemp = new sf::Texture();
    if(textureTemp->loadFromFile(textureLink))
    {
        _textures.insert(std::make_pair(textureLink, textureTemp));
        textureTemp->setSmooth(true);
        return textureTemp;
    }
    else
        delete textureTemp;

    return NULL;
}

sf::Texture* ImageManager::getTexture(const std::string &textureLink)
{
    sf::Texture *textureTemp;

    if(!searchTexture(textureLink, textureTemp))
        textureTemp = createTexture(textureLink);

    return textureTemp;
}

void ImageManager::deleteTexture(sf::Texture &texture)
{
    std::map<std::string, sf::Texture*>::iterator it;

    for(it = _textures.begin(); it != _textures.end(); it++)
    {
        if(it->second == &texture)
        {
            delete &texture;
            _textures.erase(it);
            break;
        }
    }
}

void ImageManager::deleteTexture(const std::string &textureLink)
{
    std::map<std::string, sf::Texture*>::iterator it;

    it = _textures.find(textureLink);

    if(it != _textures.end())
    {
        if(it->second != NULL)
        {
          delete (it->second);
          _textures.erase(it);
        }
    }
}
