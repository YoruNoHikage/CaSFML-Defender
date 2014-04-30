#ifndef FRIEND_HPP
#define FRIEND_HPP

#include <SFML/Graphics/Texture.hpp>

#include "character.hpp"
#include "../Alive.hpp"

class Friend : public Character
{
    public:
        Friend(const sf::Texture& texture);
        ~Friend();

        virtual void loadAnimationsFromNode(Node& root);

        virtual void nearToCastle(Castle& castle);

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);

    private:

};


#endif // FRIEND_HPP
