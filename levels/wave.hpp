#ifndef WAVE_HPP
#define WAVE_HPP

#include "../characters/enemy.hpp"
#include "../characters/Friend.hpp"
#include "../characters/character.hpp"

class Wave
{
    public:
        Wave();
        ~Wave();

        void addEnemy(Enemy* enemy);
        void addFriend(Friend* buddy);

        std::vector<Character*>& getCharacters();

    private:
        std::vector<Character*> _characters;
};

#endif // WAVE_HPP
