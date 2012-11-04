#ifndef IMAGEMANAGER_HPP
#define IMAGEMANAGER_HPP

class ImageManager
{
    public:
        ImageManager();
        ~ImageManager();

        sf::Texture* getTexture(const std::string &textureLink);
        void deleteTexture(const std::string &textureLink);
        void deleteTexture(sf::Texture &texture);

    private:
        bool searchTexture(const std::string &textureLink, sf::Texture* &textureTemp);
        sf::Texture* createTexture(const std::string &textureLink);

        std::map<std::string, sf::Texture*> _textures;
};

#endif
