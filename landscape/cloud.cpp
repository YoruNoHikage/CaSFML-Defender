#include "../config.hpp"

#include "cloud.hpp"

Cloud::Cloud() : _velocity(8.f), _appeared(false) // generate randomly
{
    load(IMAGES_PATH"cloud.png");
    getSprite().setPosition(-getSprite().getGlobalBounds().width, 50); // change the height randomly
}

Cloud::~Cloud()
{
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
       && ( getSprite().getPosition().x >= WINDOW_WIDTH
       || getSprite().getPosition().x + getSprite().getGlobalBounds().width < 0))
        return true;
    return false;
}
