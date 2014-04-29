#include "../config.hpp"

#include "wave.hpp"

Wave::Wave()
{
}

Wave::~Wave()
{
    std::for_each(_characters.begin(), _characters.end(), Deallocator<Character>());
}

void Wave::addEnemy(Enemy* enemy)
{
    _characters.push_back(enemy);
}

void Wave::addFriend(Friend* buddy)
{
    _characters.push_back(buddy);
}

std::vector<Character*>& Wave::getCharacters()
{
    return _characters;
}
