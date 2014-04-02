#include "../config.hpp"

#include <cassert>

#include "locator.hpp"

Locator::Locator()
{
}

Locator::~Locator()
{
    delete _serviceImage;
}

ImageManager* Locator::getImageManager()
{
    assert(_serviceImage != NULL);
    return _serviceImage;
}

void Locator::provideImageManager(ImageManager* service)
{
    _serviceImage = service;
}

ImageManager* Locator::_serviceImage;
