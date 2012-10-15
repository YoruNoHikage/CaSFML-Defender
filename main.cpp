#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "config.hpp"
#include "characters/character.hpp"
#include "weapons/weapon.hpp"
#include "weapons/bullet.hpp"

int main(int argc, char *argv[])
{
    sf::Texture backgroundSet, characterSet, enemySet, groundSet, castleSet, weaponSet, bulletSet;
    // write some objects to manage sprites and actions

    sf::Clock clock;
    sf::Time time1, time2;

    if(!backgroundSet.loadFromFile(PATH_IMAGES"background.png"))
        std::cout << "background.png has not been found" << std::endl;

    sf::Sprite background(backgroundSet);
    background.setScale(SCALE, SCALE);

    if(!characterSet.loadFromFile(PATH_IMAGES"character.png"))
        std::cout << "character.png has not been found" << std::endl;
    if(!weaponSet.loadFromFile(PATH_IMAGES"weapon.png"))
        std::cout << "weapon.png has not been found" << std::endl;
    if(!bulletSet.loadFromFile(PATH_IMAGES"bullet.png"))
        std::cout << "bullet.png has not been found" << std::endl;
    Character character(characterSet, weaponSet, bulletSet);

    if(!enemySet.loadFromFile(PATH_IMAGES"enemy.png"))
        std::cout << "enemy.png has not been found" << std::endl;

    sf::Sprite enemy(enemySet);
    enemy.setScale(SCALE, SCALE);

    if(!groundSet.loadFromFile(PATH_IMAGES"ground.png"))
        std::cout << "ground.png has not been found" << std::endl;

    sf::Sprite ground(groundSet);
    ground.setScale(SCALE, SCALE);

    if(!castleSet.loadFromFile(PATH_IMAGES"castle.png"))
        std::cout << "castle.png has not been found" << std::endl;

    sf::Sprite castle(castleSet);
    castle.setScale(SCALE, SCALE);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Castle Defender");

    background.setPosition((WINDOW_WIDTH - background.getGlobalBounds().width) / 2, (WINDOW_HEIGHT - background.getGlobalBounds().height) / 2);
    ground.setPosition((WINDOW_WIDTH - ground.getGlobalBounds().width) / 2, background.getPosition().y + background.getGlobalBounds().height - ground.getGlobalBounds().height);
    enemy.setPosition(50, background.getPosition().y + background.getGlobalBounds().height - enemy.getGlobalBounds().height - ground.getGlobalBounds().height / 2); // x temporary
    castle.setPosition(background.getPosition().x + background.getGlobalBounds().width - castle.getGlobalBounds().width, background.getPosition().y + background.getGlobalBounds().height - castle.getGlobalBounds().height - ground.getGlobalBounds().height / 2);
    character.setPosition(background.getPosition().x + background.getGlobalBounds().width - castle.getGlobalBounds().width,
                          background.getPosition().y + background.getGlobalBounds().height - castle.getGlobalBounds().height - ground.getGlobalBounds().height / 2 - character.getSprite().getGlobalBounds().height / 2);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    character.attack(position);
                }
            }
            else if(event.type == sf::Event::MouseWheelMoved)
            {
                // scroll
                std::cout << "mouse wheel move !" << std::endl;
            }
        }

        time1 = clock.getElapsedTime();
        if(time1 >= sf::milliseconds(100))
        {
            // do some stuff
            character.getWeapon()->getBullet()->move();
            clock.restart();
        }
        //time2 = clock.restart();
        //std::cout << time2.asMilliseconds() << std::endl;

        window.clear();

        // do some actions

        window.draw(background);
        window.draw(ground);
        window.draw(enemy);

        window.draw(character.getSprite());
        window.draw(character.getWeapon()->getSprite());
        window.draw(character.getWeapon()->getBullet()->getSprite());
        window.draw(castle);

        window.display();
    }

    return EXIT_SUCCESS;
}
