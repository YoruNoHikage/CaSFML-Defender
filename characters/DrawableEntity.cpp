#include "../game.hpp"
#include "DrawableEntity.hpp"

#include <SFML/Graphics/CircleShape.hpp> // debugging origin points

DrawableEntity::DrawableEntity(const sf::Texture& texture) : _animations(),
                                                             _currentAnimation(),
                                                             _texture(texture)
{
}

DrawableEntity::~DrawableEntity()
{
}

void DrawableEntity::createAnimation(const int name, const sf::IntRect& animationArea, const sf::IntRect& spriteArea, const sf::Time duration)
{
    sf::Sprite sprite(_texture, animationArea);

    _animations.insert(std::pair<const int, Animation>(name,Animation()));
    _animations[name].create(sprite, spriteArea, duration);
}

void DrawableEntity::setAnimation(const int name)
{
    _animations[_currentAnimation].reset();
    _currentAnimation = name;
}

sf::IntRect DrawableEntity::loadAreaFromNode(Node& node) const
{
    sf::IntRect area;
    area.left = atoi(node.firstAttributeValue("left").c_str());
    area.top = atoi(node.firstAttributeValue("top").c_str());
    area.width = atoi(node.firstAttributeValue("width").c_str());
    area.height = atoi(node.firstAttributeValue("height").c_str());

    return area;
}

void DrawableEntity::updateCurrent(sf::Time elapsedTime)
{
    _animations[_currentAnimation].update(elapsedTime);
}

void DrawableEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(_animations.size() != 0)
    {
        const Animation& anim = _animations.find(_currentAnimation)->second;
        target.draw(anim, states);

        if(Game::getContext().getDebug())
            drawDebug(target, states);
    }
}

void DrawableEntity::drawDebug(sf::RenderTarget& target, sf::RenderStates states) const
{
    // debug origin point
    sf::CircleShape debug(4);
    debug.setPosition(getOrigin());
    debug.setOrigin(4, 4);
    debug.setFillColor(sf::Color(0, 0, 255, 50));
    target.draw(debug, states);
}

sf::IntRect DrawableEntity::getTextureRect() const
{
    if(_animations.size() != 0)
    {
        const Animation& anim = _animations.find(_currentAnimation)->second;
        return anim.getTextureRect();
    }

    return sf::IntRect();
}

sf::FloatRect DrawableEntity::getGlobalBounds() const
{
    if(_animations.size() != 0)
    {
        const Animation& anim = _animations.find(_currentAnimation)->second;
        return anim.getGlobalBounds();
    }

    return sf::FloatRect();
}

sf::FloatRect DrawableEntity::getLocalBounds() const
{
    if(_animations.size() != 0)
    {
        const Animation& anim = _animations.find(_currentAnimation)->second;
        return anim.getLocalBounds();
    }

    return sf::FloatRect();
}

void DrawableEntity::loadAnimationsFromNode(Node& root)
{
    // The first node has to be "entity"
    if(root.getName() != "entity")
    {
        std::string error = "Error : first node has to be \"entity\"";
        throw std::runtime_error(error);
    }

    Node& animationsNode = root.firstChild("animations");
    std::vector<Node*> animations = animationsNode.getChildren("animation");
    for(std::vector<Node*>::iterator animItr = animations.begin() ; animItr != animations.end() ; ++animItr)
    {
        int type;
        if((*animItr)->firstAttributeValue("name") == "blink")
            type = DrawableEntity::BLINK;
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
}
