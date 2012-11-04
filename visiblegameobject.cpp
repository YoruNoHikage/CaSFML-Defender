#include "config.hpp"
#include "visiblegameobject.hpp"

VisibleGameObject::VisibleGameObject() : _isLoaded(false)
{
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::load(std::string filename)
{
    ImageManager *im = Locator::getImageManager();
    _texture = im->getTexture(filename);
    if(_texture == NULL)
    {
        _filename = "";
        _isLoaded = false;
    }
    else
    {
        _filename = filename;
        _sprite.setTexture(*_texture);
        _sprite.setScale(SCALE, SCALE);
        _isLoaded = true;
    }
}

void VisibleGameObject::draw(sf::RenderWindow& window)
{
    if(_isLoaded)
        window.draw(_sprite);
}

void VisibleGameObject::update(sf::Time elapsedTime)
{
}


void VisibleGameObject::setPosition(float x, float y)
{
    if(_isLoaded)
        _sprite.setPosition(x, y);
}

sf::Vector2f VisibleGameObject::getPosition() const
{
    if(_isLoaded)
        return _sprite.getPosition();
    return sf::Vector2f();
}

bool VisibleGameObject::isLoaded() const
{
    return _isLoaded;
}

sf::Sprite& VisibleGameObject::getSprite()
{
    return _sprite;
}
