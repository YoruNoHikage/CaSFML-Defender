#include "config.hpp"
#include "game.hpp"

#include "hitbox/boundingboxhitbox.hpp"
#include "castle.hpp"

#include "tools/locator.hpp"
#include "tools/imagemanager.hpp"

Castle::Castle() : SpriteNode(),
                   Collidable(),
                   Alive(),
                   _isLoaded(false)
{
}

Castle::~Castle()
{
}

void Castle::load(std::string filename)
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

    _hitbox = new BoundingBoxHitbox(getGlobalBounds());
    _hitbox->setPosition(getPosition().x, getPosition().y);
}

void Castle::updateCurrent(sf::Time elapsedTime)
{
    SpriteNode::updateCurrent(elapsedTime);

    // nothing to do here
}

void Castle::drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const
{
    SpriteNode::drawCurrent(target, states);
    if(_hitbox && Game::getContext().getDebug())
        _hitbox->drawDebug(target, states);
}
