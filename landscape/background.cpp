#include "../config.hpp"

#include "background.hpp"

Background::Background()
{
    //temporary
    _clouds.push_back(new Cloud());
}

Background::~Background()
{
    std::for_each(_clouds.begin(), _clouds.end(), CloudDeallocator());
}

void Background::update(sf::Time elapsedTime)
{
    for(std::list<Cloud*>::iterator it = _clouds.begin() ; it != _clouds.end() ; ++it)
    {
        if((*it)->hasToBeRemoved())
        {
            delete *it;
            _clouds.erase(it);
            std::cout << "Cloud deleted" << std::endl;
        }
        else
            (*it)->update(elapsedTime);
    }
}

void Background::draw(sf::RenderWindow& window)
{
    VisibleGameObject::draw(window);
    for(std::list<Cloud*>::iterator it = _clouds.begin() ; it != _clouds.end() ; ++it)
    {
        (*it)->draw(window);
    }
}
