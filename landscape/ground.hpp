#ifndef GROUND_HPP
#define GROUND_HPP

#include "cloud.hpp"

class Ground : public VisibleGameObject
{
    public:
        Ground();
        ~Ground();

        void load(std::string filename);
};

#endif

