#ifndef GROUND_HPP
#define GROUND_HPP

#include "../SpriteNode.hpp"
#include "../Collidable.hpp"
#include "cloud.hpp"

class Ground : public SpriteNode, public Collidable
{
    public:
        Ground();
        ~Ground();

        void load(std::string filename);

    protected:

        virtual void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    private:
        bool _isLoaded;
};

#endif

