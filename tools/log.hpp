#ifndef LOG_HPP
#define LOG_HPP

#include <string>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Err.hpp>

class Log : public sf::NonCopyable
{
    public:

        enum Type { LOG_ERROR, LOG_WARNING, LOG_INFO };

        template<typename T>
        static void write(Type type, T object)
        {
            std::string prefix("");
            switch(type)
            {
                case Log::LOG_ERROR:
                    prefix = "[ERROR] : ";
                    break;
                case Log::LOG_WARNING:
                    prefix = "[warning] : ";
                    break;
                case Log::LOG_INFO:
                    prefix = "[info] : ";
                    break;
                default:
                    prefix = "[other] : ";
                    break;
            }

            sf::err() << prefix << object << std::endl;
        }
};

#endif // LOG_HPP
