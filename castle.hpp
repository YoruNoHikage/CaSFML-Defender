#ifndef CASTLE_HPP
#define CASTLE_HPP

#include "visiblegameobject.hpp"

class Castle : public VisibleGameObject
{
    public:
        Castle();
        ~Castle();

        void load(std::string filename);

    private:
        int life;
};

#endif
