#include "../config.hpp"
#include "splashscreen.hpp"

/** \brief ctor
 */
SplashScreen::SplashScreen()
{
}

/** \brief dtor
 */
SplashScreen::~SplashScreen()
{
}

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

void SplashScreen::init()
{
    if(!_splashTexture.loadFromFile(IMAGES_PATH"splashscreen.png"))
    {
        std::cerr << "Error loading splashcreen.png" << std::endl;
        return;
    }

    _splash.setTexture(_splashTexture);
}

/** \brief Update the splashscreen (event detection)
 *
 * \param elapsedTime sf::Time
 * \return void
 *
 */
void SplashScreen::update(sf::Time elapsedTime)
{
}

/** \brief Draw the splashscreen
 *
 * \param app sf::RenderWindow&
 * \return void
 *
 */
void SplashScreen::draw(sf::RenderWindow& app)
{
    app.draw(sprite);
}

/** \brief Launched when the splashscreen is loaded in the state machine
 *
 * \return void
 *
 */
void SplashScreen::onEnter()
{
}

/** \brief Launched when the splashscreen is ended in the state machine
 *
 * \return void
 *
 */
void SplashScreen::onExit()
{
}
