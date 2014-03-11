#ifndef CONFIG_HPP
#define CONFIG_HPP

///@todo: delete standard & SFML dependencies, keeping just define

#include <iostream>
#include <map>
#include <cmath>
#include <list> // please remove it, bad perfs
#include <vector>
#include <cstdlib>
#include <typeinfo>

// Errors
#include <stdexcept> // To throw exceptions
#include <cassert> // To cut the program during debug, disable it in the release please

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

// tools
#include "tools/imagemanager.hpp"

#include "tools/locator.hpp"
#include "tools/log.hpp"

#include "context.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

#define VIEW_WIDTH 1280
#define VIEW_HEIGHT 720

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

#include <sstream>

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

#include <SFML/Graphics/Rect.hpp>
template <typename T>
std::string toString(const sf::Rect<T>& value)
{
    std::stringstream stream;
    stream << "Rect(" << value.left << ";" << value.top << " - " << value.width << ";" << value.height << ") ";
    return stream.str();
}

#include <SFML/System/Vector2.hpp>
template <typename T>
std::string toString(const sf::Vector2<T>& value)
{
    std::stringstream stream;
    stream << "Vector2(" << value.x << ";" << value.y << ") ";
    return stream.str();
}

#endif

