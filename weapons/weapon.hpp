#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../SceneNode.hpp"
#include "../visiblegameobject.hpp"

class Weapon : public VisibleGameObject, public SceneNode
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
        virtual void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    private:
        float _angle;
        sf::Time _rechargingTime, _elapsedTime;
};

#endif
