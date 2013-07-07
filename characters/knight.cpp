#include "../config.hpp"

#include "enemyfactory.hpp"
#include "knight.hpp"

/** \brief ctor
 */
Knight::Knight()
{
}

/** \brief dtor
 */
Knight::~Knight()
{
}

bool Knight::registered = Factory<Enemy>::GetFactory().registration("Knight", &createInstance<Knight>);
