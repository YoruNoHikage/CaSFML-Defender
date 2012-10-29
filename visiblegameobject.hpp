#ifndef VISIBLEGAMEOBJECT_HPP
#define VISIBLEGAMEOBJECT_HPP

class VisibleGameObject
{
    public:
        VisibleGameObject();
        virtual ~VisibleGameObject();

        virtual void load(std::string filename);
        virtual void draw(sf::RenderWindow& window);
        virtual void update(sf::Time elapsedTime);

        virtual void setPosition(float x, float y);
        virtual sf::Vector2f getPosition() const;
        virtual bool isLoaded() const;

    protected:
        sf::Sprite& getSprite();

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        std::string _filename;
        bool _isLoaded;
};

#endif

