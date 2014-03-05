#include "../config.hpp"

#include "../game.hpp"
#include "player.hpp"

Player::Player(const sf::Texture& texture) : Character(texture),
                                             _head(texture),
                                             _body(texture),
                                             _arm(texture),
                                             _foot(texture)
{
    ///@todo: Put that into a xml file
    _foot.createAnimation(0, sf::IntRect(115, 600, 100, 190), sf::IntRect(115, 600, 100, 190), sf::seconds(1));
    _foot.setPosition(0, 100);
    _foot.setOrigin(50, 50); // not used for children, point to the ground
    attachChild(&_foot);

    _body.createAnimation(0, sf::IntRect(0, 325, 174, 280), sf::IntRect(0, 325, 174, 280), sf::seconds(1));
    _body.setOrigin(90, 150);
    attachChild(&_body);

    _head.createAnimation(0, sf::IntRect(0, 0, 300, 325), sf::IntRect(0, 0, 300, 325), sf::seconds(1));
    _head.setPosition(100, 5);
    _head.setOrigin(200, 307);
    _body.attachChild(&_head);

    _arm.createAnimation(0, sf::IntRect(0, 795, 200, 45), sf::IntRect(0, 795, 200, 45), sf::seconds(1));
    _arm.setOrigin(180, 25);
    _arm.setPosition(100, 75);
    _body.attachChild(&_arm);
}

Player::~Player()
{
}

void Player::load(std::string filename, std::string fWeapon)
{
    Character::load(filename, fWeapon);

    detachChild(*_weapon);
    _arm.attachChild(_weapon);
}

void Player::updateCurrent(sf::Time elapsedTime)
{
    /////////////////////////////////////
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        // if mouse button left is pressed, the character attacks
        attack(elapsedTime, Game::getContext().getApp().mapPixelToCoords(sf::Mouse::getPosition(Game::getContext().getApp())));
    /////////////////////////////////////

    // We get the mouse position relative to the window
    sf::Vector2f clicPos = Game::getContext().getApp().mapPixelToCoords(sf::Mouse::getPosition(Game::getContext().getApp()));

    // The points to track
    sf::Vector2f armOrigin = (_arm.getWorldTransform() * _arm.getOrigin());
    sf::Vector2f bodyOrigin = (_body.getWorldTransform() * _body.getOrigin());

    sf::Vector2f deltaArm = clicPos - armOrigin;
    sf::Vector2f deltaBody = clicPos - bodyOrigin;

    if(deltaArm.x == 0)
        deltaArm.x = 1; // avoid division by 0
    if(deltaBody.x == 0)
        deltaBody.x = 1; // avoid division by 0

    float bodyAngle = (std::atan(deltaBody.y / deltaBody.x) / (M_PI * 2)) * 360 / 4;
    // we substract the body angle because the body rotates too
    float armAngle = (std::atan(deltaArm.y / deltaArm.x) / (M_PI * 2)) * 360 - bodyAngle;

    ///@todo: fix here
    if(deltaArm.x > 0 || deltaBody.x > 0)
    {
        setScale(- std::abs(getScale().x), getScale().y);
        bodyAngle *= -1;
        armAngle *= -1;
    }
    else
        setScale(std::abs(getScale().x), getScale().y);

    _body.setRotation(bodyAngle);
    _arm.setRotation(armAngle);
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw nothing because we don't want a player background
}

void Player::attack(sf::Time elapsedTime, sf::Vector2f location)
{
    getWeapon()->shoot(elapsedTime, location);
}
