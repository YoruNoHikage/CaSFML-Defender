#ifndef CLOUD_HPP
#define CLOUD_HPP

#include "../visiblegameobject.hpp"

class Cloud : public VisibleGameObject
{
    public:
        Cloud();
        ~Cloud();

        virtual void update(sf::Time elapsedTime);
        bool hasToBeRemoved();

    private:
        float _velocity;
        bool _appeared;
};

#endif
