#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <map>
#include <stdexcept>

#include "log.hpp"

template <typename T>
struct AbstractCreator
{
    virtual T* operator()(const sf::Texture& texture) const = 0;
};

template <typename T, typename D>
struct Creator : public AbstractCreator<T>
{
    D* operator()(const sf::Texture& texture) const
    {
        return new D(texture);
    }
};

/** \brief Factory class to create any child registrated of the type T
 *
 */
template <typename T>
class Factory
{
    public:

        typedef std::map<std::string, AbstractCreator<T>*> MapStringCreators;

        ~Factory()
        {
            Log::write(Log::LOG_INFO, "Factory deleted");
            for(typename MapStringCreators::iterator itr = _types.begin() ; itr != _types.end() ; ++itr)
                delete itr->second;
        };

        static Factory<T>& getFactory() { static Factory<T> instance; return instance; }

        template <typename Derived>
        bool registration(const std::string& key)
        {
            Log::write(Log::LOG_INFO, "Registration in Factory of type : " + key);
            return _types.insert(std::pair<std::string, AbstractCreator<T>*>(key, new Creator<T, Derived>())).second;
        }

        T* build(const std::string& key, sf::Texture& texture) const
        {
            typename MapStringCreators::const_iterator it = _types.find(key);
            if (it == _types.end())
                throw std::runtime_error(std::string("The type " + key + " you asking for doesn't exist."));

            const AbstractCreator<T>& creator = *(it->second);
            return creator(texture);
        }

    private:
        MapStringCreators _types;
};

#endif // FACTORY_HPP
