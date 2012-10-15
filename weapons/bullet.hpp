#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet
{
    public:
        Bullet(sf::Texture &texture);
        void move();
        sf::Sprite getSprite();

    private:
        sf::Sprite sprite;
};


#endif

