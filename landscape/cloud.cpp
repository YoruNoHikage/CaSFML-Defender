#include "../config.hpp"

#include "cloud.hpp"

Cloud::Cloud() : _velocity((rand() % (10 - (-10) + 1) - 10)), _appeared(false)
{
}

Cloud::~Cloud()
{
}

void Cloud::load(std::string filename)
{
    VisibleGameObject::load(filename);
    if(isLoaded())
    {
        int y = rand() % (VIEW_HEIGHT - 100 - (int)getSprite().getGlobalBounds().height) + 1; // TO DO : put the ground's height instead of 100

        if(_velocity > 0)
            getSprite().setPosition(-getSprite().getGlobalBounds().width, y);
        else
            getSprite().setPosition(VIEW_WIDTH + getSprite().getGlobalBounds().width, y);

        int scale = rand() % 2 + 1;
        getSprite().setScale(scale, scale);
    }
}

void Cloud::update(sf::Time elapsedTime)
{
    if(isLoaded())
    {
        getSprite().move(_velocity * elapsedTime.asSeconds() , 0);
        if(!_appeared)
            _appeared = true;
    }
    else
        _appeared = true;
}

bool Cloud::hasToBeRemoved()
{
    if(_appeared
       && ( getSprite().getPosition().x > VIEW_WIDTH + getSprite().getLocalBounds().width
       || getSprite().getPosition().x + getSprite().getGlobalBounds().width < 0))
        return true;
    return false;
}
