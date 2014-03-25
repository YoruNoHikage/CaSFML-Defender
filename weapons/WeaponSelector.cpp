#include "../config.hpp"

#include "../game.hpp"

#include "WeaponSelector.hpp"

WeaponSelector::WeaponSelector(SceneNode& weaponParent) : _weapons(),
                                                                _currentSelection(0),
                                                                _tmpSelection(0),
                                                                _backgrounds(sf::Quads),
                                                                _weaponParent(weaponParent),
                                                                _elapsedTime(sf::seconds(10)), // used to avoid first transition
                                                                _isSelectionning(false),
                                                                _cursorOut(true)
{
    setPosition(10, 10);
}

WeaponSelector::~WeaponSelector()
{
    std::for_each(_weapons.begin(), _weapons.end(), Deallocator<Weapon>());
}

void WeaponSelector::addWeapon(Weapon* weapon)
{
    int count = _backgrounds.getVertexCount();
    _backgrounds.resize(count + 4); // We add 4 vertices, it's Quads

    for(int i = 0 ; i < 4 ; i++)
    {
        _backgrounds[count + i].color = sf::Color(34, 177, 76);
        _backgrounds[count + i].position = sf::Vector2f(0, 0);
    }

    _weapons.push_back(weapon);
    if(_weapons.size() == 1)
        _weaponParent.attachChild(weapon);
}

Weapon& WeaponSelector::getWeapon() const
{
    return *_weapons[_currentSelection];
}

void WeaponSelector::activateSelection()
{
    _isSelectionning = true;
    _elapsedTime = sf::Time::Zero;
}

void WeaponSelector::updateCurrent(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && _elapsedTime > sf::milliseconds(100))
    {
        Log::write(Log::LOG_INFO, "Now selectionning weapon");
        _isSelectionning = !_isSelectionning;
        _elapsedTime = sf::Time::Zero;
    }

    ///@todo: reverse the vector so it can draw first thumbnail on top

    _cursorOut = true;
    for(std::size_t i = 0 ; i < _weapons.size() ; i++)
    {
        /// Positions ///

        int indexVertex = i * 4;
        int margin = 10, width = 100, height = 100;
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
        else // activate the selection
            activateSelection();
    }
}

void WeaponSelector::changeWeapon(std::size_t selection)
{
    _weaponParent.detachChild(*_weapons[_currentSelection]);

    _currentSelection = selection;

    _weaponParent.attachChild(_weapons[_currentSelection]);
}

void WeaponSelector::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // loop for every weapon
    target.draw(_backgrounds, states);
}
