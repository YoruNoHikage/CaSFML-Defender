#ifndef WEAPONSELECTOR_HPP
#define WEAPONSELECTOR_HPP

#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "../SceneNode.hpp"
#include "weapon.hpp"

class WeaponSelector : public SceneNode
{
    public:
        struct Thumbnail
        {
            static const int margin = 10;
            sf::Sprite sprite;

            Weapon* weapon;
        };

        typedef std::vector<Thumbnail> ThumbnailArray;

        WeaponSelector(SceneNode& weaponParent);
        ~WeaponSelector();

        void addWeapon(Weapon* weapon);

        Weapon& getWeapon() const;

    protected:

        void activateSelection(bool activate);
        void updateSelections(int index, sf::FloatRect rect);

    private:

        void changeWeapon(std::size_t selection);
        void resizeThumbnailsSprite(Thumbnail& thumbnail);

        virtual void updateCurrent(sf::Time elapsedTime);

        // draw stack
        virtual void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

        ThumbnailArray _thumbnails;
        std::size_t _currentSelection,
                    _tmpSelection;

        sf::VertexArray _backgrounds;
        SceneNode& _weaponParent; // attach to the arm

        sf::Time _elapsedTime;
        bool _isSelectionning,
             _cursorOut;

        ///@todo: replace by an image's height/width ?
        static const int _backgroundWidth = 100,
                         _backgroundHeight = 100,
                         _marginBackground = 10;
};


#endif // WEAPONSELECTOR_HPP
