#ifndef SHOT_HPP
#define SHOT_HPP

#include "../visiblegameobject.hpp"

class Shot : public VisibleGameObject
{
    public:
        Shot(sf::Vector2i location);
        ~Shot();

        void update(sf::Time elapsedTime);

    private:
        int _damage;
        float _velocity, _coeff, _deltaX, _deltaY;
        sf::Vector2i _location; // position where the shot goes
};

#endif
