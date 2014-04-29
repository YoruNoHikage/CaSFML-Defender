#ifndef DRAWABLEENTITY_HPP
#define DRAWABLEENTITY_HPP

#include <map>
#include <string>

#include <SFML/Graphics/Texture.hpp>

#include "../tools/node.hpp"

#include "../SceneNode.hpp"
#include "Animation.hpp"

class DrawableEntity : public SceneNode
{
    public:
        typedef std::map<const int, Animation> MapAnimations;

        DrawableEntity(const sf::Texture& texture);
        virtual ~DrawableEntity();

        /** \brief Creates an animation with a texture' subarea
         *
         * \param name const int Name of the animation to create, usually an enumeration
         * \param animationArea const sf::IntRect& The area containing all sprite's animation
         * \param spriteArea const sf::IntRect& The sprite's area relative to the animationArea
         * \param duration const sf::Time The duration of the complete animation
         *
         * \return void
         */
        void createAnimation(const int name, const sf::IntRect& animationArea, const sf::IntRect& spriteArea, const sf::Time duration);

        /** \brief Sets the current animation
         *
         * \param name const int Name of the animation, usually an enumeration define in a derived class
         *
         * \return void
         */
        void setAnimation(const int name);

        enum Type{BLINK}; // this is the basic animations for drawable entities
        virtual void loadAnimationsFromNode(Node& root);

        /// Please add an enumeration like enum AnimationsName{RUNNING, JUMPING, JUMPING2};

        virtual sf::IntRect getTextureRect() const;
        virtual sf::FloatRect getGlobalBounds() const;
        virtual sf::FloatRect getLocalBounds() const;

    protected:

        /** \brief Loads an area from a node and returns the IntRect corresponding to it
         *
         * \param node Node&
         * \return sf::IntRect
         *
         */
        sf::IntRect loadAreaFromNode(Node& node) const;

        /** \brief Updates the current animation which has to be drawn
          *
          * \param elapsedTime Elapsed time since the last clock restart
          *
          * \return void
          */
        void updateCurrent(sf::Time elapsedTime);

        /** \brief Draws the current animation into the target
          *
          * \param target The target to draw to
          * \param states Current render states
          *
          * \return void
          */
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void drawDebug(sf::RenderTarget& target, sf::RenderStates states) const;

    private:

        MapAnimations _animations;
        int _currentAnimation;

        const sf::Texture& _texture;
};


#endif // DRAWABLEENTITY_HPP
