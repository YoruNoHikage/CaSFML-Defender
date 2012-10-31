#include "config.hpp"

#include "castle.hpp"

Castle::Castle() : life(100)
{
    load(IMAGES_PATH"castle.png");
    assert(isLoaded());
    getSprite().setPosition(WINDOW_WIDTH - getSprite().getGlobalBounds().width, WINDOW_HEIGHT - getSprite().getGlobalBounds().height - 50); // TO DO : write ground's height instead of 50
}

Castle::~Castle()
{
}
