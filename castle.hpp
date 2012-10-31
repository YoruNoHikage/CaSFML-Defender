#ifndef CASTLE_HPP
#define CASTLE_HPP

#include "visiblegameobject.hpp"

class Castle : public VisibleGameObject
{
    public:
        Castle();
        ~Castle();

    private:
        int life;
};

#endif
