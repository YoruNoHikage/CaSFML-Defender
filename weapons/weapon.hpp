#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../SpriteNode.hpp"

class Weapon : public SpriteNode
{
    public:
        Weapon();
        virtual ~Weapon();

        virtual void load(std::string filename);

        void shoot(sf::Time elapsedTime, sf::Vector2f location);

        void setAngle(float angle);
        float getAngle() const;

    protected:
        virtual void updateCurrent(sf::Time elapsedTime);

    private:
        float _angle;
        sf::Time _rechargingTime,
                 _elapsedTime;

        bool _isLoaded;
};

#endif
