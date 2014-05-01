#include "../config.hpp"

#include "../game.hpp"
#include "character.hpp"

#include "../hitbox/boundingboxhitbox.hpp"

Character::Character(const sf::Texture& texture) : DrawableEntity(texture),
                                                   Collidable(),
                                                   Alive(),
                                                   _weapon(NULL),
                                                   _direction(1),
                                                   _velocity(0.1f),
                                                   _nearToCastle(false)
{
}

Character::~Character()
{
    if(_weapon != NULL)
        delete _weapon;
}

void Character::load(std::string filename, std::string fWeapon)
{
    _weapon = new Weapon();
    _weapon->load(fWeapon);
    attachChild(_weapon);
}

void Character::loadEntityFromNode(Node& root)
{
    DrawableEntity::loadEntityFromNode(root);

    Hitbox* hitbox(NULL);
    try
    {
        Node& areaNode = root.firstChild("hitbox");
        sf::FloatRect area = static_cast<sf::FloatRect>(loadAreaFromNode(areaNode));
        hitbox = new BoundingBoxHitbox(getPosition(), area);
    }
    catch(std::runtime_error& e)
    {
        Log::write(Log::LOG_WARNING, "No hitbox defined for Entity : " + toString(e.what()));
        // when there isn't hitbox, we assign the entity's global bounds as a hitbox
        hitbox = new BoundingBoxHitbox(getPosition(), getGlobalBounds());
    }
    setHitbox(hitbox);
    Log::write(Log::LOG_INFO, "Friend's hitbox creation : " + toString(getGlobalBounds()));
}

void Character::updateCurrent(sf::Time elapsedTime)
{
    DrawableEntity::updateCurrent(elapsedTime);

    _hitbox->setPosition(getPosition().x, getPosition().y);

    if(!isNearToCastle())
        goToCastle(elapsedTime);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    DrawableEntity::drawCurrent(target, states);
    if(_hitbox && Game::getContext().getDebug())
        _hitbox->drawDebug(target, states);
}

Weapon* Character::getWeapon()
{
    return _weapon;
}

bool Character::isNearToCastle() const
{
    return _nearToCastle;
}

void Character::nearToCastle(Castle& castle)
{
    _nearToCastle = true;
}

void Character::goToCastle(sf::Time elapsedTime)
{
    move(_velocity * elapsedTime.asMilliseconds(), 0);
}
