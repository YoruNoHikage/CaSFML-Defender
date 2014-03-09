#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "cloud.hpp"

class Background : public SpriteNode
{
    public:
        typedef std::list<Cloud*> CloudList;

        Background();
        ~Background();

        void load(std::string filename);

        void generateClouds();

    protected:

        void updateCurrent(sf::Time elapsedTime);

    private:
        CloudList _clouds;

        bool _isLoaded;
};

#endif
