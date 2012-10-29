#include "../config.hpp"
#include "splashscreen.hpp"

void SplashScreen::show(sf::RenderWindow& window)
{
    sf::Texture texture;
    if(!texture.loadFromFile(IMAGES_PATH"splashscreen.png"))
    {
        std::cerr << "Error loading splashcreen.png" << std::endl;
        return;
    }

    sf::Sprite sprite(texture);

    window.draw(sprite);

    window.display();

    sf::Event event; // wait or poll ? depends on the action
    while(window.waitEvent(event))
    {
        if(event.type == sf::Event::KeyPressed
           || event.type == sf::Event::MouseButtonPressed
           || event.type == sf::Event::Closed)
        {
            return;
        }
    }
}
