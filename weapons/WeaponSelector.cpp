#include "../config.hpp"

#include "../game.hpp"

#include "WeaponSelector.hpp"

WeaponSelector::WeaponSelector(SceneNode& weaponParent) : _currentSelection(0),
                                                          _tmpSelection(0),
                                                          _backgrounds(sf::Quads),
                                                          _weaponParent(weaponParent),
                                                          _elapsedTime(sf::seconds(10)), // used to avoid first transition
                                                          _isSelectionning(false),
                                                          _cursorOut(true)
{
    setPosition(_marginBackground, _marginBackground);
}

WeaponSelector::~WeaponSelector()
{
    for(std::size_t i = 0 ; i < _thumbnails.size() ; i++)
        delete _thumbnails[i].weapon;
}

void WeaponSelector::addWeapon(Weapon* weapon)
{
    // Vertices for background
    int count = _backgrounds.getVertexCount();
    _backgrounds.resize(count + 4); // We add 4 vertices, it's Quads

    for(int i = 0 ; i < 4 ; i++)
    {
        _backgrounds[count + i].color = sf::Color(34, 177, 76);
        _backgrounds[count + i].position = sf::Vector2f(0, 0);
    }

    Thumbnail thumb;
    thumb.sprite = weapon->getSprite();
    thumb.weapon = weapon;
    resizeThumbnailsSprite(thumb);

    _thumbnails.push_back(thumb);

    Log::write(Log::LOG_INFO, "Scale thumbnail : " + toString(thumb.sprite.getScale()));

    if(_thumbnails.size() == 1)
        _weaponParent.attachChild(_thumbnails[0].weapon);
}

Weapon& WeaponSelector::getWeapon() const
{
    return *_thumbnails[_currentSelection].weapon;
}

void WeaponSelector::activateSelection(bool activate)
{
    Log::write(Log::LOG_INFO, "Now (un)selectionning weapon");
    _isSelectionning = activate;
    _elapsedTime = sf::Time::Zero;
}

void WeaponSelector::updateCurrent(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;

    _cursorOut = true;
    for(std::size_t i = 0 ; i < _thumbnails.size() ; i++)
    {
        /// Positions ///

        int indexVertex = i * 4;
        int margin = _marginBackground, width = _backgroundWidth, height = _backgroundHeight;
        int x = (margin + width) * i, y = 0;
        float currentX = (i+1) * 200.f * _elapsedTime.asSeconds();

        if(_isSelectionning)
        {
            if(currentX < x)
                x = currentX;
        }
        else // Back to the old position
        {
            currentX = x - currentX;
            if(currentX > 0)
                x = currentX;
            else
                x = 0;
        }

        _backgrounds[indexVertex].position = sf::Vector2f(x, y);
        _backgrounds[indexVertex + 1].position = sf::Vector2f(x + width, y);
        _backgrounds[indexVertex + 2].position = sf::Vector2f(x + width, y + height);
        _backgrounds[indexVertex + 3].position = sf::Vector2f(x, y + height);
        _thumbnails[i].sprite.setPosition(x + (width / 2 - _thumbnails[i].sprite.getGlobalBounds().width / 2),
                                          y + (height / 2 - _thumbnails[i].sprite.getGlobalBounds().height / 2));

        updateSelections(i, sf::FloatRect(x, y, width, height));

        /// Color ///

        sf::Color color;
        if(i == _tmpSelection || i == _currentSelection)
            color = sf::Color(237, 28, 36);
        else
            color = sf::Color(34, 177, 76);

        _backgrounds[indexVertex].color = color;
        _backgrounds[indexVertex + 1].color = color;
        _backgrounds[indexVertex + 2].color = color;
        _backgrounds[indexVertex + 3].color = color;
    }

    if(_cursorOut)
        _tmpSelection = _currentSelection;
}

void WeaponSelector::updateSelections(int index, sf::FloatRect rect)
{
    const sf::RenderWindow& app = Game::getContext().getApp();
    const sf::Vector2f& location = app.mapPixelToCoords(sf::Mouse::getPosition(app));

    if(!_isSelectionning)
    {
        rect.left = _backgrounds[0].position.x;
        rect.top = _backgrounds[0].position.y;
    }

    rect = getWorldTransform().transformRect(rect);
    if(rect.contains(location))
    {
        // The selection moves
        if(_isSelectionning)
        {
            _tmpSelection = index;
            _cursorOut = false;
        }
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && _elapsedTime > sf::milliseconds(100))
    {
        if(_backgrounds.getBounds().contains(location)) // if we click inside the selector
        {
            if(_isSelectionning) // if player is selectionning, just pick the new weapon
                changeWeapon(_tmpSelection);
            activateSelection(!_isSelectionning); // and deactivate selectionning
        }
        else if(_isSelectionning) // if we click outside, we are not selectionning anymore
            activateSelection(false);
    }
}

void WeaponSelector::changeWeapon(std::size_t selection)
{
    _weaponParent.detachChild(*_thumbnails[_currentSelection].weapon);

    _currentSelection = selection;

    _weaponParent.attachChild(_thumbnails[_currentSelection].weapon);
}

void WeaponSelector::resizeThumbnailsSprite(Thumbnail& thumbnail)
{
    sf::FloatRect bounds = thumbnail.sprite.getGlobalBounds();
    float ratio = bounds.width / bounds.height;
    float scale = 1.f;

    if(ratio > 1.f)
        scale = (_backgroundWidth - thumbnail.margin * 2) / bounds.width;
    else
        scale = (_backgroundHeight - thumbnail.margin * 2) / bounds.height;

    thumbnail.sprite.setScale(scale, scale);
}

void WeaponSelector::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // We draw the weapons
    for(std::size_t i = 0 ; i < _thumbnails.size() ; i++)
    {
        if(i != _currentSelection)
        {
            target.draw(&_backgrounds[i * 4], 4, sf::Quads, states);
            target.draw(_thumbnails[i].sprite, states);
        }
    }

    // and the selection on top
    target.draw(&_backgrounds[_currentSelection * 4], 4, sf::Quads, states);
    target.draw(_thumbnails[_currentSelection].sprite, states);
}
