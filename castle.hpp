#ifndef CASTLE_HPP
#define CASTLE_HPP

#include "SpriteNode.hpp"
#include "Collidable.hpp"

class Castle : public SpriteNode, public Collidable, public Alive
{
    public:
        Castle();
        ~Castle();

        void load(std::string filename);

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);
        void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    private:
        bool _isLoaded;
};

#endif
