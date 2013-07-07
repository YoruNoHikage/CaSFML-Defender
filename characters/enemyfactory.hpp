#ifndef ENEMYFACTORY_HPP
#define ENEMYFACTORY_HPP

// try to improve !
// write the destructor pleeeease

/** \brief Create instance of a Enemy's derived object
 *
 * \return Enemy*
 *
 * TO DO : Remove the Enemy object to do something more flexible and change the file to the tools folder
 */
template<class Derived> Enemy* createInstance() { return new Derived(); }

/** \brief Factory class to create any child registrated of the type T
 *
 */
template <typename T>
class Factory
{
    public:
        static Factory<T>& GetFactory() { static Factory<T>* e = new Factory<T>(); return *e; }

        bool registration(const std::string& key, Enemy* (*ptr)())
        {
            return _types.insert(std::pair<std::string, Enemy*(*)()>(key, ptr)).second;
        }

        T* build(const std::string& key) const
        {
            typename std::map<std::string, Enemy*(*)()>::const_iterator it = _types.find(key);
            if (it == _types.end())
                throw std::runtime_error(std::string("The type " + key + " you asking for doesn't exist."));
            return (it->second)();
        }

    private:
        std::map<std::string, Enemy*(*)()> _types;
};

#endif // ENEMYFACTORY_HPP
