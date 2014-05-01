#ifndef CASTLE_HPP
#define CASTLE_HPP

#include "characters/DrawableEntity.hpp"
#include "Collidable.hpp"
#include "BarDisplay.hpp"

class Castle : public DrawableEntity, public Collidable, public Alive
{
    public:
        Castle(const sf::Texture& texture);
        ~Castle();

        void load(std::string filename);

        virtual void loadEntityFromNode(Node& root);

    protected:

        virtual void updateCurrent(sf::Time elapsedTime);
        void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;

    private:
        BarDisplay _healthBar;
};

#endif
