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

        virtual void loadEntityFromNode(Node& root);

        virtual void nearToCastle(Castle& castle);

        bool isSaved() { return _saved; };

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);

    private:
        bool _saved;
};


#endif // FRIEND_HPP
