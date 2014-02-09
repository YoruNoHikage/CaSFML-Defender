#include <iostream>

#include "Animation.hpp"

Animation::Animation() : _sprite(),
                         _frameRect(),
                         _numberFrames(0),
                         _currentFrame(0),
                         _duration(sf::Time::Zero),
                         _repeat(true),
                         _elapsedTime(sf::Time::Zero),
                         _isLoaded(false)
{
}

Animation::~Animation()
{
}

void Animation::create(const sf::Sprite& spritesheet, const sf::IntRect spriteArea, sf::Time duration)
{
    // We get the first's frame rect
    _frameRect = spriteArea;
    // The number of sprites there is on this area
    _numberFrames = spritesheet.getTextureRect().width / spriteArea.width;

    // Setting the texture to own it
    _sprite.setTexture(*spritesheet.getTexture());
    _sprite.setTextureRect(spriteArea);

    // the duration of the animation
    _duration = duration;

    // we can say the animation is ready
    _isLoaded = true;
}

/// @todo: compatibility with multiple lines spritesheet
void Animation::update(sf::Time elapsedTime)
{
    sf::Time timePerFrame = _duration / static_cast<float>(_numberFrames);
    _elapsedTime += elapsedTime;

    while(_isLoaded && _elapsedTime >= timePerFrame && (_currentFrame <= _numberFrames || _repeat))
    {
        _currentFrame++;
        if(_currentFrame >= _numberFrames && _repeat)
            _currentFrame = 0;

        _elapsedTime -= timePerFrame;
    }

    sf::IntRect textureRect(_frameRect.left + _currentFrame * _frameRect.width,
                            _frameRect.top, ///@todo: here
                            _frameRect.width,
                            _frameRect.height);

    _sprite.setTextureRect(textureRect);
}

void Animation::reset()
{
    _currentFrame = 0;
}

bool Animation::isLoaded()
{
    return _isLoaded;
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(_isLoaded)
    {
        states.transform *= getTransform();
        target.draw(_sprite, states);
    }
}
