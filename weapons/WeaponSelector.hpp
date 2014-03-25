#ifndef WEAPONSELECTOR_HPP
#define WEAPONSELECTOR_HPP

#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "../SceneNode.hpp"

class WeaponSelector : public SceneNode
{
    public:
        typedef std::vector<Weapon*> WeaponArray;

        WeaponSelector(SceneNode& weaponParent);
        ~WeaponSelector();

        void addWeapon(Weapon* weapon);

        Weapon& getWeapon() const;

    protected:

        void activateSelection();
        void updateSelections(int index, sf::FloatRect rect);

    private:

        void changeWeapon(std::size_t selection);

        virtual void updateCurrent(sf::Time elapsedTime);

        // draw stack
        virtual void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

        WeaponArray _weapons;
        std::size_t _currentSelection,
                    _tmpSelection;

        sf::VertexArray _backgrounds;
        SceneNode& _weaponParent;

        sf::Time _elapsedTime;
        bool _isSelectionning,
             _cursorOut;
};


#endif // WEAPONSELECTOR_HPP
