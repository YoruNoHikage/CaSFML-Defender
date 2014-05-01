#ifndef BARDISPLAY_HPP
#define BARDISPLAY_HPP

#include "SpriteNode.hpp"

#include <SFML/Graphics/Sprite.hpp>

class BarDisplay : public SpriteNode
{
    public:
        BarDisplay();
        BarDisplay(unsigned int maxRectValue);
        void init();

        ~BarDisplay();

        int getValue() { return _value; };
        int getMaxValue() { return _maxValue; };

        void setValue(const int value);
        void setMaxValue(const int maxValue);

    protected:

        void updateCurrent(sf::Time elapsedTime);

    private:
        int _value,
            _maxValue,
            _maxRectValue;
};


#endif // BARDISPLAY_HPP
