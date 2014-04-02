#include "../config.hpp"

#include "../tools/locator.hpp"

#include "background.hpp"

Background::Background() : _clouds(),
                           _isLoaded(false)
{
}

Background::~Background()
{
    std::for_each(_clouds.begin(), _clouds.end(), Deallocator<Cloud>());
}

void Background::load(std::string filename)
{
    ImageManager *im = Locator::getImageManager();
    sf::Texture* texture = im->getTexture(IMAGES_PATH + filename);
    if(texture == NULL)
        _isLoaded = false;
    else
    {
        _sprite.setTexture(*texture);
        _isLoaded = true;
    }
}

void Background::generateClouds()
{
    while(_clouds.size() < 3)
    {
        Cloud *newCloud = new Cloud();
        _clouds.push_back(newCloud);
        newCloud->load("cloud.png");

        attachChild(newCloud);
    }
}

void Background::updateCurrent(sf::Time elapsedTime)
{
    for(std::list<Cloud*>::iterator it = _clouds.begin() ; it != _clouds.end() ; ++it)
    {
        if((*it)->hasToBeRemoved())
        {
            detachChild(**it);
            delete *it;
            it = _clouds.erase(it);
        }
        else
            (*it)->update(elapsedTime);
    }
    generateClouds();
}

