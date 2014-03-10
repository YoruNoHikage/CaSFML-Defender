#include "../config.hpp"

#include "../game.hpp"
#include "player.hpp"

Player::Player(const sf::Texture& texture) : Character(texture),
                                             _head(texture),
                                             _body(texture),
                                             _arm(texture),
                                             _foot(texture)
{
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

void Player::loadFromNode(Node& root)
{
    ///@todo: this can be in the parent class
    // The first node has to be "entity"
    if(root.getName() != "entity")
    {
        std::string error = "Error : first node has to be \"entity\"";
        throw std::runtime_error(error);
    }

    // We fill the entity's attributes
    //_life = root.firstAttributeValue("life");

    ///////////// MEMBERS PART /////////////

    Node& membersNode = root.firstChild("members");

    Node& footNode = membersNode.firstChild("foot");
    sf::IntRect footArea = loadAreaFromNode(footNode);
    ///@todo: currently no animations, but maybe in the future
    //_foot.createAnimation(0, footArea, footArea, sf::seconds(1)); // no animation, so 0 is perfect and 1 second
    _foot.createAnimation(0, sf::IntRect(115, 600, 100, 190), sf::IntRect(115, 600, 100, 190), sf::seconds(1));
    _foot.setPosition(0, 100);
    _foot.setOrigin(50, 50); // not used for children, point to the ground
    attachChild(&_foot);
    Log::write(Log::LOG_INFO, "Member part : Foot texture region : " + toString(footArea.left) + ";" + toString(footArea.top)
               + " - size : " + toString(footArea.width) + ";" + toString(footArea.height));

    Node& bodyNode = membersNode.firstChild("body");
    sf::IntRect bodyArea = loadAreaFromNode(bodyNode);
    //_body.createAnimation(0, bodyArea, bodyArea, sf::seconds(1));
    _body.createAnimation(0, sf::IntRect(0, 325, 174, 280), sf::IntRect(0, 325, 174, 280), sf::seconds(1));
    _body.setOrigin(90, 150);
    attachChild(&_body);
    Log::write(Log::LOG_INFO, "Member part : Body texture region : " + toString(bodyArea.left) + ";" + toString(bodyArea.top)
               + " - size : " + toString(bodyArea.width) + ";" + toString(bodyArea.height));

    Node& headNode = membersNode.firstChild("head");
    sf::IntRect headArea = loadAreaFromNode(headNode);
    _head.createAnimation(0, headArea, headArea, sf::seconds(1));
    _head.setPosition(100, 5);
    _head.setOrigin(200, 307);
    _body.attachChild(&_head);
    Log::write(Log::LOG_INFO, "Member part : Head texture region : " + toString(headArea.left) + ";" + toString(headArea.top)
               + " - size : " + toString(headArea.width) + ";" + toString(headArea.height));

    Node& armNode = membersNode.firstChild("arm");
    sf::IntRect armArea = loadAreaFromNode(armNode);
    _arm.createAnimation(0, armArea, armArea, sf::seconds(1));
    _arm.setOrigin(180, 25);
    _arm.setPosition(100, 75);
    _body.attachChild(&_arm);
    Log::write(Log::LOG_INFO, "Member part : Arm texture region : " + toString(armArea.left) + ";" + toString(armArea.top)
               + " - size : " + toString(armArea.width) + ";" + toString(armArea.height));
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

sf::FloatRect Player::getGlobalBounds() const
{
    ///@todo: if there's no animation currently, return the addition of every bounds
    return Character::getGlobalBounds();
}

sf::FloatRect Player::getLocalBounds() const
{
    ///@todo: how to deal with localbounds if there's no animation ?
    return Character::getLocalBounds();
}
