#include "../config.hpp"

#include "enemy.hpp"

Enemy::Enemy(const sf::Texture& texture) : Character(texture),
                                           _velocity(0.1f),
                                           _nearToCastle(false)
{
}

Enemy::~Enemy()
{
}

void Enemy::load(std::string filename)
{
    Character::load(filename);
}

void Enemy::load(std::string filename, std::string fWeapon)
{
    Character::load(filename, fWeapon);
}

void Enemy::updateCurrent(sf::Time elapsedTime)
{
    Character::updateCurrent(elapsedTime);
    if(!_nearToCastle)
        goToCastle(elapsedTime);
    else
        attack(elapsedTime);

    _hitbox->setPosition(getPosition().x, getPosition().y);
}

void Enemy::goToCastle(sf::Time elapsedTime)
{
    move(_velocity * elapsedTime.asMilliseconds(), 0);
}

void Enemy::nearToCastle()
{
    _nearToCastle = true;
}

bool Enemy::isNearToCastle() const
{
    return _nearToCastle;
}

void Enemy::attack(sf::Time elapsedTime)
{
    //if(getWeapon() != NULL)
        // attack avec l'arme
}

void Enemy::die()
{
    _isAlive = false;
}

void Enemy::loadAnimationsFromNode(Node& root)
{
    // The first node has to be "entity"
    if(root.getName() != "entity")
    {
        std::string error = "Error : first node has to be \"entity\"";
        throw std::runtime_error(error);
    }

    // We fill the entity's attributes
    //_life = root.firstAttributeValue("life");

    Node& animationsNode = root.firstChild("animations");
    std::vector<Node*> animations = animationsNode.getChildren("animation");
    for(std::vector<Node*>::iterator animItr = animations.begin() ; animItr != animations.end() ; ++animItr)
    {
        Enemy::Type type;
        if((*animItr)->firstAttributeValue("name") == "blink")
            type = Enemy::BLINK;
        else
            continue;

        sf::Time duration(sf::seconds(atof((*animItr)->firstAttributeValue("duration").c_str())));

        sf::IntRect area;
        Node& areaNode = (*animItr)->firstChild("area");
        area.top = atoi(areaNode.firstAttributeValue("top").c_str());
        area.left = atoi(areaNode.firstAttributeValue("left").c_str());
        area.width = atoi(areaNode.firstAttributeValue("width").c_str());
        area.height = atoi(areaNode.firstAttributeValue("height").c_str());

        sf::IntRect spriteArea;
        Node& spriteAreaNode = (*animItr)->firstChild("spritearea");
        spriteArea.top = atoi(spriteAreaNode.firstAttributeValue("top").c_str());
        spriteArea.left = atoi(spriteAreaNode.firstAttributeValue("left").c_str());
        spriteArea.width = atoi(spriteAreaNode.firstAttributeValue("width").c_str());
        spriteArea.height = atoi(spriteAreaNode.firstAttributeValue("height").c_str());

        createAnimation(type, area, spriteArea, duration);
    }

    setAnimation(Enemy::BLINK);
}
