#include "../config.hpp"

#include <cassert>

#include <SFML/Window/Mouse.hpp>

#include "../tools/locator.hpp"

#include "splashscreen.hpp"

/** \brief ctor
 *
 * \param stateMachine StateMachine&
 *
 */
SplashScreen::SplashScreen(StateMachine& stateMachine) : _stateMachine(stateMachine)
{
    init();
}

/** \brief dtor
 */
SplashScreen::~SplashScreen()
{
}

/** \brief Initialize textures and sprites
 *
 * \return void
 *
 */
void SplashScreen::init()
{
    ImageManager* im = Locator::getImageManager();
    _splashTexture = im->getTexture(IMAGES_PATH"splashscreen.png");
    assert(_splashTexture != NULL);

    _splash.setTexture(*_splashTexture);
}

/** \brief Update the splashscreen (event detection)
 *
 * \param elapsedTime sf::Time
 * \return void
 *
 */
void SplashScreen::update(sf::Time elapsedTime)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        _stateMachine.change("playingscreen");
}

/** \brief Draw the splashscreen
 *
 * \param app sf::RenderWindow&
 * \return void
 *
 */
void SplashScreen::draw(sf::RenderWindow& app)
{
    app.draw(_splash);
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
