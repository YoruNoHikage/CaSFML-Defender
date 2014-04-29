#ifndef CONFIG_HPP
#define CONFIG_HPP

// tools

#include "tools/log.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

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

