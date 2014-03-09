#ifndef CLOUD_HPP
#define CLOUD_HPP

#include "../SpriteNode.hpp"

class Cloud : public SpriteNode
{
    public:
        Cloud();
        ~Cloud();

        void load(std::string filename);
        bool hasToBeRemoved();

    protected:

        void updateCurrent(sf::Time elapsedTime);
        void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    protected:

        float _velocity;
        bool _appeared,
             _isLoaded;
};

#endif
