#ifndef CLOUD_HPP
#define CLOUD_HPP

#include "../visiblegameobject.hpp"

class Cloud : public VisibleGameObject
{
    public:
        Cloud();
        ~Cloud();

        void load(std::string filename);
        void update(sf::Time elapsedTime);
        bool hasToBeRemoved();

    private:
        float _velocity;
        bool _appeared;
};

#endif
