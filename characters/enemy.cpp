#include "../config.hpp"

#include <stdexcept>

#include "enemy.hpp"

Enemy::Enemy(const sf::Texture& texture) : Character(texture),
                                           _healthBar(),
                                           _damages(1)
{
    attachChild(&_healthBar);
}

Enemy::~Enemy()
{
}

void Enemy::loadAnimationsFromNode(Node& root)
{
    DrawableEntity::loadAnimationsFromNode(root);

    Node& animationsNode = root.firstChild("animations");
    std::vector<Node*> animations = animationsNode.getChildren("animation");
    for(std::vector<Node*>::iterator animItr = animations.begin() ; animItr != animations.end() ; ++animItr)
    {
        int type;
        if((*animItr)->firstAttributeValue("name") == "attack")
            type = Enemy::ATTACK;
        else
            continue;

        sf::Time duration(sf::seconds(atof((*animItr)->firstAttributeValue("duration").c_str())));

        Node& areaNode = (*animItr)->firstChild("area");
        sf::IntRect area = loadAreaFromNode(areaNode);

        Node& spriteAreaNode = (*animItr)->firstChild("spritearea");
        sf::IntRect spriteArea = loadAreaFromNode(spriteAreaNode);

        createAnimation(type, area, spriteArea, duration);
    }

    setAnimation(DrawableEntity::BLINK);

    // We fill the entity's attributes
    int life = atoi(root.firstAttributeValue("life").c_str());
    setLife(life);

    ////// Enemy's children //////

    // we set the healthbar
    _healthBar.setMaxValue(getLife());
    _healthBar.setPosition(getGlobalBounds().width / 2 - _healthBar.getGlobalBounds().width / 2,
                           - _healthBar.getGlobalBounds().height * 2);

    try
    {
        loadWeaponFromNode(root.firstChild("weapon"));
    }
    catch(std::runtime_error& e)
    {
        Log::write(Log::LOG_ERROR, "The enemy doesn't have a weapon D: \n "
                   + toString(e.what()));
    }
}

void Enemy::loadWeaponFromNode(Node& root)
{
    _damages = atoi(root.firstAttributeValue("damages").c_str());
}

void Enemy::updateCurrent(sf::Time elapsedTime)
{
    Character::updateCurrent(elapsedTime);

    if(isNearToCastle())
    {
        setAnimation(Enemy::ATTACK);
        attack(elapsedTime);
    }

    _healthBar.setValue(getLife());
}

void Enemy::attack(sf::Time elapsedTime)
{
    if(/*getWeapon() != NULL &&*/ _targetCastle != NULL)
    {
        _targetCastle->receiveDamages(_damages);
    }
}

void Enemy::nearToCastle(Castle& castle)
{
    Character::nearToCastle(castle);
    _targetCastle = &castle; // So we can destroy it, nyahaahahahahaha
}
