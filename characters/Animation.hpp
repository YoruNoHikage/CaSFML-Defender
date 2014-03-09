#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

/** \brief Animated Sprite
 */
class Animation : public sf::Drawable, public sf::Transformable
{
    public:

        /** \brief ctor
         */
        Animation();

        /** \brief dtor
         */
        virtual ~Animation();

        /** \brief Split the spritesheet given into multiples sprites to perform the animation
         *
         * \param spritesheet const sf::Sprite&
         * \param spriteArea const sf::IntRect
         * \return void
         *
         */
        void create(const sf::Sprite& spritesheet, const sf::IntRect spriteArea, sf::Time duration);

        /** \brief update the current sprite which has to be drawn
          *
          * \param elapsedTime elapsed time since the last clock restart
          */
        void update(sf::Time elapsedTime);

        /** \brief Reset the animation to the beginning
         *
         * \return void
         *
         */
        void reset();

        /** \brief return is the animation is ready to update/draw
         *
         * \return bool
         *
         */
        bool isLoaded();

        virtual sf::IntRect getTextureRect() const;
        virtual sf::FloatRect getGlobalBounds() const;
        virtual sf::FloatRect getLocalBounds() const;

    protected:

        /** \brief draw the current sprite into the target
          *
          * \param target The target to draw to
          * \param states Current render states
          * \return void
          */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:

        sf::Sprite _sprite;
        sf::IntRect _frameRect;
        std::size_t _numberFrames;
        std::size_t _currentFrame;
        sf::Time _duration;
        bool _repeat;

        sf::Time _elapsedTime;

        bool _isLoaded;
};


#endif // ANIMATION_HPP
