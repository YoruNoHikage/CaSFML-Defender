#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <map>
#include <stdexcept>

///@todo: write the destructor pleeeease

/** \brief Factory class to create any child registrated of the type T
 *
 */
template <typename T>
class Factory
{
    public:

        /** \brief Create instance of a T's derived object
         *
         * \return T*
         */
        template<class Derived> static T* createInstance() { return new Derived(); }

        static Factory<T>& GetFactory() { static Factory<T>* e = new Factory<T>(); return *e; }

        bool registration(const std::string& key, T* (*ptr)())
        {
            return _types.insert(std::pair<std::string, T*(*)()>(key, ptr)).second;
        }

        T* build(const std::string& key) const
        {
            typename std::map<std::string, T*(*)()>::const_iterator it = _types.find(key);
            if (it == _types.end())
                throw std::runtime_error(std::string("The type " + key + " you asking for doesn't exist."));
            return (it->second)();
        }

    private:
        std::map<std::string, T*(*)()> _types;
};

#endif // FACTORY_HPP
