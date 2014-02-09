#ifndef SHOT_HPP
#define SHOT_HPP

#include "../visiblegameobject.hpp"

class Shot : public VisibleGameObject
{
    public:
        Shot(sf::Vector2f location, float _angle, Weapon *weapon);
        ~Shot();

        void load(std::string filename);
        void update(sf::Time elapsedTime);
        void die();

        bool hasToBeRemoved();

    private:
        int _damage;
        float _velocity, _coeff, _deltaX, _deltaY;
        sf::Vector2f _location; // position where the shot goes
        float _angle;
        Weapon *_weapon;
};

#endif
