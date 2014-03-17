#include "../config.hpp"

#include "enemy.hpp"

Enemy::Enemy(const sf::Texture& texture) : Character(texture),
                                           Alive(),
                                           _velocity(0.1f),
                                           _nearToCastle(false),
                                           _healthBar()
{
    attachChild(&_healthBar);
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
    _healthBar.setValue(getLife());
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

void Enemy::loadAnimationsFromNode(Node& root)
{
    // The first node has to be "entity"
    if(root.getName() != "entity")
    {
        std::string error = "Error : first node has to be \"entity\"";
        throw std::runtime_error(error);
    }

    // We fill the entity's attributes
    int life = atoi(root.firstAttributeValue("life").c_str());
    setLife(life);

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

        Node& areaNode = (*animItr)->firstChild("area");
        sf::IntRect area = loadAreaFromNode(areaNode);

        Node& spriteAreaNode = (*animItr)->firstChild("spritearea");
        sf::IntRect spriteArea = loadAreaFromNode(spriteAreaNode);

        createAnimation(type, area, spriteArea, duration);
    }

    setAnimation(Enemy::BLINK);

    ////// Enemy's children //////

    // we set the healthbar
    _healthBar.setMaxValue(getLife());
    _healthBar.setPosition(getGlobalBounds().width / 2 - _healthBar.getGlobalBounds().width / 2,
                           - _healthBar.getGlobalBounds().height * 2);
}
