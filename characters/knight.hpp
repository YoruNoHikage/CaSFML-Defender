#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "enemy.hpp"

/** \brief Knight class
 */
class Knight : public Enemy
{
    public:
        Knight();
        ~Knight();

    private:
        static bool registered;
};

#endif // KNIGHT_HPP
