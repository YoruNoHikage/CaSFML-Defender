#include "config.hpp"
#include "game.hpp"

#include "hitbox/boundingboxhitbox.hpp"
#include "castle.hpp"

#include "tools/locator.hpp"
#include "tools/imagemanager.hpp"

Castle::Castle(const sf::Texture& texture) : DrawableEntity(texture),
                                             Collidable(),
                                             Alive(),
                                             _healthBar(100)
{
    attachChild(&_healthBar);
}

Castle::~Castle()
{
}

void Castle::load(std::string filename)
{
}

void Castle::loadEntityFromNode(Node& root)
{
    DrawableEntity::loadEntityFromNode(root);

    // add new animations

    Hitbox* hitbox(NULL);
    try
    {
        Node& areaNode = root.firstChild("hitbox");
        sf::FloatRect area = static_cast<sf::FloatRect>(loadAreaFromNode(areaNode));
        hitbox = new BoundingBoxHitbox(getPosition(), area);
        Log::write(Log::LOG_INFO, "Castle's hitbox creation : " + toString(area));
    }
    catch(std::runtime_error& e)
    {
        Log::write(Log::LOG_WARNING, "No hitbox defined for Castle : " + toString(e.what()));
        // when there isn't hitbox, we assign the entity's global bounds as a hitbox
        hitbox = new BoundingBoxHitbox(getPosition(), getGlobalBounds());
        Log::write(Log::LOG_INFO, "Castle's hitbox creation : " + toString(getGlobalBounds()));
    }
    setHitbox(hitbox);

    // We fill the entity's attributes
    int life = atoi(root.firstAttributeValue("life").c_str());
    setLife(life);

    _healthBar.setMaxValue(getLife());
    _healthBar.setPosition(getGlobalBounds().width / 2 - _healthBar.getGlobalBounds().width / 2,
                           - _healthBar.getGlobalBounds().height * 2);
}

void Castle::updateCurrent(sf::Time elapsedTime)
{
    DrawableEntity::updateCurrent(elapsedTime);

    if(!isAlive())
        Game::getContext().gameOver(false);

    _healthBar.setValue(getLife());
}

void Castle::drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const
{
    DrawableEntity::drawCurrent(target, states);
    if(_hitbox && Game::getContext().getDebug())
        _hitbox->drawDebug(target, states);
}
