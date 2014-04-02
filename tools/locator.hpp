#ifndef IMAGEINTERFACE_HPP
#define IMAGEINTERFACE_HPP

#include "imagemanager.hpp"

class Locator
{
    public:
        Locator();
        ~Locator();
        static ImageManager* getImageManager();

        static void provideImageManager(ImageManager* service);

    private:
        static ImageManager* _serviceImage;
};

#endif
