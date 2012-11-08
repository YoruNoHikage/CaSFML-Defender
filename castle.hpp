#ifndef CASTLE_HPP
#define CASTLE_HPP

#include "visiblegameobject.hpp"

class Castle : public VisibleGameObject
{
    public:
        Castle();
        ~Castle();

        void load(std::string filename);

        void update(sf::Time elapsedTime);

    private:
        int life;
};

#endif
