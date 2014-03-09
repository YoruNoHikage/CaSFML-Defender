#include <algorithm>

#include "scenenode.hpp"

SceneNode::SceneNode() : _parent(NULL),
                         _children()
{

}

void SceneNode::attachChild(SceneNode* child)
{
    child->_parent = this;
    _children.push_back(child);
}

SceneNode* SceneNode::detachChild(const SceneNode& node)
{
    std::vector<SceneNode*>::iterator found = std::find(_children.begin(), _children.end(), &node);
    //assert(found != _children.end());

    SceneNode* result = *found;
    result->_parent = NULL;
    _children.erase(found);

    return result;
}

void SceneNode::update(sf::Time elapsedTime)
{
    updateCurrent(elapsedTime);
    updateChildren(elapsedTime);
}

void SceneNode::updateCurrent(sf::Time elapsedTime)
{
    // Do nothing by default
}

void SceneNode::updateChildren(sf::Time elapsedTime)
{
    for(SceneNode::ArraySceneNode::const_iterator itr = _children.begin() ; itr != _children.end() ; ++itr)
        (*itr)->update(elapsedTime);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and children with changed transform
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(SceneNode::ArraySceneNode::const_iterator itr = _children.begin() ; itr != _children.end() ; ++itr)
        (*itr)->draw(target, states);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != NULL ; node = node->_parent)
        transform = node->getTransform() * transform;

    return transform;
}

sf::FloatRect SceneNode::getGlobalBounds() const
{
    // we don't know the size
    return sf::FloatRect();
}

sf::FloatRect SceneNode::getLocalBounds() const
{
    // we don't know the size
    return sf::FloatRect();
}
