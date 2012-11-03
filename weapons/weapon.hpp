#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../visiblegameobject.hpp"

class Weapon : public VisibleGameObject
{
    public:
        Weapon();
        virtual ~Weapon();

        virtual void load(std::string filename);

        void shoot(sf::Time elapsedTime, sf::Vector2i location);

        virtual void update(sf::Time elapsedTime);

        void setAngle(float angle);
        float getAngle() const;

    private:
        float _angle;
        sf::Time _rechargingTime, _elapsedTime;
};

#endif
