#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <vector>
#include <memory>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::vector<SceneNode*> ArraySceneNode;

        SceneNode();

        void attachChild(SceneNode* child);
        SceneNode* detachChild(const SceneNode& node);

        void update(sf::Time elapsedTime);

        sf::Vector2f getWorldPosition() const;
        sf::Transform getWorldTransform() const;

        virtual sf::IntRect getDimension() const;

    private:

        virtual void updateCurrent(sf::Time elapsedTime);
        void updateChildren(sf::Time elapsedTime);

        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
        virtual void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;
        void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        ArraySceneNode _children;
        SceneNode* _parent;
};

#endif // SCENENODE_HPP
