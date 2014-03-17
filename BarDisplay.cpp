#include "config.hpp"
#include "BarDisplay.hpp"

#include "tools/imagemanager.hpp"

BarDisplay::BarDisplay() : SpriteNode(),
                           _value(0),
                           _maxValue(0),
                           _maxRectValue(50)
{
    ImageManager *im = Locator::getImageManager();
    sf::Texture* texture = im->getTexture(IMAGES_PATH"healthbar.png");
    if(texture != NULL)
    {
        _sprite.setTexture(*texture);
        _sprite.setTextureRect(sf::IntRect(0, 0, _maxRectValue, 10));
    }
}

BarDisplay::~BarDisplay()
{
}

void BarDisplay::setValue(const int value)
{
    value > 0 ? _value = value : _value = 0;
}

void BarDisplay::setMaxValue(const int maxValue)
{
    if(maxValue > 0)
        _maxValue = maxValue;
}

void BarDisplay::updateCurrent(sf::Time elapsedTime)
{
    int width = 0;
    if(_maxValue >= _value)
        width = static_cast<int>( static_cast<float>(_value) / _maxValue * _maxRectValue );

    _sprite.setTextureRect(sf::IntRect(0, 0, width, 10));
}
