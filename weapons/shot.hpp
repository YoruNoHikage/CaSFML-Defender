#ifndef SHOT_HPP
#define SHOT_HPP

#include "../Collidable.hpp"
#include "../SpriteNode.hpp"

class Shot : public SpriteNode, public Collidable
{
    public:
        Shot(sf::Vector2f location, float _angle, Weapon *weapon);
        ~Shot();

        void load(std::string filename);
        void die();

        bool hasToBeRemoved();

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);
        virtual void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    private:
        int _damage;
        float _velocity, _coeff, _deltaX, _deltaY;
        sf::Vector2f _location; // position where the shot goes
        float _angle;
        Weapon *_weapon;

        bool _isLoaded,
             _isAlive;
};

#endif
