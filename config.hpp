#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <map>
#include <cassert>
#include <cmath>
#include <list>
#include <cstdlib>
#include <typeinfo>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

// tools
#include "tools/imagemanager.hpp"

#include "tools/locator.hpp"

#include "context.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768

#define SCALE 1.f

#define IMAGES_PATH "data/images/"
#define LEVELS_PATH "data/levels/"

/* Global needs */
template <typename T>
struct Deallocator
{
    void operator()(const T* p) const
    {
        delete p;
    }
};

#endif

