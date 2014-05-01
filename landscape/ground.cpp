#include "../config.hpp"
#include "../game.hpp"

#include "../tools/locator.hpp"

#include "../hitbox/boundingboxhitbox.hpp"
#include "ground.hpp"

Ground::Ground() : SpriteNode(),
                   Collidable(),
                   _isLoaded(false)
{
}

Ground::~Ground()
{
}

void Ground::load(std::string filename)
{
    ImageManager *im = Locator::getImageManager();
    sf::Texture* texture = im->getTexture(IMAGES_PATH + filename);
    if(texture == NULL)
        _isLoaded = false;
    else
    {
        _sprite.setTexture(*texture, true); // We want to reset the textureRect so we set reset to true
        _isLoaded = true;
    }

    setPosition(0, VIEW_HEIGHT - getGlobalBounds().height);

    sf::FloatRect rect(getPosition().x,
                         getPosition().y + getGlobalBounds().height / 2, // the collision is in the ground's middle
                         getGlobalBounds().width,
                         getGlobalBounds().height / 2);
    _hitbox = new BoundingBoxHitbox(rect);

    Log::write(Log::LOG_INFO, std::string("Loading ground : position " + toString(getPosition()) + toString(getGlobalBounds())));
    Log::write(Log::LOG_INFO, std::string("Ground sprite hitbox : " + toString(rect)));
}

void Ground::drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const
{
    SpriteNode::drawCurrent(target, states);
    if(_hitbox && Game::getContext().getDebug())
        _hitbox->drawDebug(target, states);
}
