#ifndef IMAGEINTERFACE_HPP
#define IMAGEINTERFACE_HPP

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
