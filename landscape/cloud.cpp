#include "../config.hpp"

#include "cloud.hpp"

Cloud::Cloud() : _velocity((rand() % (10 - (-10) + 1) - 10)),
                 _appeared(false),
                 _isLoaded(false)
{
}

Cloud::~Cloud()
{
}

void Cloud::load(std::string filename)
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

    if(_isLoaded)
    {
        int y = rand() % (VIEW_HEIGHT - 100 - static_cast<int>(getGlobalBounds().height)) + 1; ///@todo: put the ground's height instead of 100

        if(_velocity > 0)
            _sprite.setPosition(-getGlobalBounds().width, y);
        else
            _sprite.setPosition(VIEW_WIDTH + getGlobalBounds().width, y);

        float scale = (static_cast<float>(rand()) / RAND_MAX) * (1 - 0.5) + 0.5;
        _sprite.setScale(scale, scale);
    }
}

bool Cloud::hasToBeRemoved()
{
    if(_appeared
       && ( _sprite.getPosition().x > VIEW_WIDTH + getGlobalBounds().width
       || _sprite.getPosition().x + getGlobalBounds().width < 0))
        return true;
    return false;
}

void Cloud::updateCurrent(sf::Time elapsedTime)
{
    if(_isLoaded)
    {
        _sprite.move(_velocity * elapsedTime.asSeconds() , 0);
        if(!_appeared)
            _appeared = true;
    }
    else
        _appeared = true;
}

void Cloud::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
