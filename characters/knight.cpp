#include "../config.hpp"

#include "../tools/factory.hpp"
#include "knight.hpp"

/** \brief ctor
 */
Knight::Knight(const sf::Texture& texture) : Enemy(texture)
{
}

/** \brief dtor
 */
Knight::~Knight()
{
}

//bool Knight::registered = Factory<Enemy>::GetFactory().registration("Knight", &Factory<Enemy>::createInstance<Knight>);
