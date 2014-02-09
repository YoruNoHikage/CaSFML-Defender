#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <map>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Animation.hpp"

typedef std::map<const int, Animation> MapAnimations;

class DrawableEntity : public sf::Drawable, public sf::Transformable
{
    public:
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

        /// Please add an enumeration like enum AnimationsName{RUNNING, JUMPING, JUMPING2};

        /** \brief Updates the current animation which has to be drawn
          *
          * \param elapsedTime Elapsed time since the last clock restart
          *
          * \return void
          */
        void update(sf::Time elapsedTime);

    protected:

        /** \brief Draws the current animation into the target
          *
          * \param target The target to draw to
          * \param states Current render states
          *
          * \return void
          */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:

        MapAnimations _animations;
        int _currentAnimation;

        const sf::Texture& _texture;
};


#endif // ENTITY_HPP
