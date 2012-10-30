#ifndef BACKGROUND_CPP
#define BACKGROUND_CPP

#include "cloud.hpp"

class Background : public VisibleGameObject
{
    public:
        Background();
        ~Background();

        void generateClouds();

        virtual void update(sf::Time elapsedTime);
        virtual void draw(sf::RenderWindow& window);

    private:
        std::list<Cloud*> _clouds;
        struct CloudDeallocator
        {
            void operator()(const Cloud* p) const
            {
                delete p;
            }
        };
};

#endif
