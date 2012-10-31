#include "../config.hpp"

#include "background.hpp"

Background::Background()
{
}

Background::~Background()
{
    std::for_each(_clouds.begin(), _clouds.end(), CloudDeallocator());
}

void Background::generateClouds()
{
    while(_clouds.size() < 3)
    {
        _clouds.push_back(new Cloud());
    }
}

void Background::update(sf::Time elapsedTime)
{
    for(std::list<Cloud*>::iterator it = _clouds.begin() ; it != _clouds.end() ; ++it)
    {
        if((*it)->hasToBeRemoved())
        {
            delete *it;
            it = _clouds.erase(it);
            //it--;
            std::cout << "Cloud deleted" << std::endl;
        }
        else
            (*it)->update(elapsedTime);
    }
    generateClouds();
}

void Background::draw(sf::RenderWindow& window)
{
    VisibleGameObject::draw(window);
    for(std::list<Cloud*>::iterator it = _clouds.begin() ; it != _clouds.end() ; ++it)
    {
        (*it)->draw(window);
    }
}