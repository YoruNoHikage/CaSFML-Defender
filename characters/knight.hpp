#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "enemy.hpp"

/** \brief Knight class
 */
class Knight : public Enemy
{
    public:
        Knight(const sf::Texture& texture);
        ~Knight();

    private:
        static const bool registered;
};

#endif // KNIGHT_HPP
