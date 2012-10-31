#ifndef GAMEOBJECTMANAGER_HPP
#define GAMEOBJECTMANAGER_HPP

#include "visiblegameobject.hpp"

class GameObjectManager
{
    public:
        GameObjectManager();
        ~GameObjectManager();

        void add(std::string name, VisibleGameObject* gameObject);
        void remove(std::string name);
        int getObjectCount() const;
        VisibleGameObject* get(std::string name) const;

        void updateAll(sf::Time elapsedTime);
        void drawAll(sf::RenderWindow& window);

    private:

        // TO DO : Try to organize in the opposite
        struct OrderAsList // ranks the elements in the std::map in the opposite of the addition's order
        {
            bool operator()(const std::string& a, const std::string& b) const
            {
                return true;
            }
        };

        std::map<std::string, VisibleGameObject*, OrderAsList> _gameObjects;

        struct GameObjectDeallocator
        {
            void operator()(const std::pair<std::string, VisibleGameObject*>& p) const
            {
                delete p.second;
            }
        };


};

#endif
