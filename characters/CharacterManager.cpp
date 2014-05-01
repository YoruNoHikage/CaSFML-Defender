#include "../config.hpp"

#include "CharacterManager.hpp"
#include "../game.hpp"

CharacterManager::CharacterManager() : _generationTime(sf::seconds(1.f)), _noMoreCharacters(false), _charactersLeft(0)
{
}

CharacterManager::~CharacterManager()
{
    std::for_each(_characters.begin(), _characters.end(), Deallocator<Character>());
}

void CharacterManager::reset()
{
    std::for_each(_characters.begin(), _characters.end(), Deallocator<Character>());
    _characters.clear();
}

void CharacterManager::generateCharacters()
{
    Wave* newWave = Game::getContext().getLevel().getNextWave();
    if(newWave != NULL)
    {
        while(newWave->getCharacters().size() > 0)
        {
            Character* character = newWave->getCharacters().front();
            newWave->getCharacters().erase(newWave->getCharacters().begin());
            _characters.push_back(character);
        }
    }
    else
        _noMoreCharacters = true;
}

void CharacterManager::getNewCharacters(sf::Time elapsedTime)
{
    if(Game::getContext().getCharacters().size() == 0)
        _waveOver = true;

    if(_characters.size() == 0)
        generateCharacters();
    else if(_waveOver)
    {
        _elapsedTime += elapsedTime;
        if(_elapsedTime > _generationTime)
        {
            Game::getContext().addCharacter(_characters.front());
            _characters.erase(_characters.begin());

            _elapsedTime = sf::Time::Zero;
        }

        if(_characters.size() == 0)
            _waveOver = false;
    }
}
