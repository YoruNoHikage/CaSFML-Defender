#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "DrawableEntity.hpp"
#include "../weapons/WeaponSelector.hpp"

class Player : public DrawableEntity
{
    public:
        Player(const sf::Texture& texture);
        ~Player();

        void loadFromNode(Node& root);

        void addWeaponToStack(Weapon* weapon);

        void attack(sf::Time elapsedTime, sf::Vector2f location);

        sf::FloatRect getGlobalBounds() const;
        sf::FloatRect getLocalBounds() const;

    private:

        void updateCurrent(sf::Time elapsedTime);

        void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

        void fillPartsFromNode(Node& node, DrawableEntity& part);

    private:
        DrawableEntity _head,
                       _body,
                       _arm,
                       _foot;

        WeaponSelector _weapons;
};

#endif

