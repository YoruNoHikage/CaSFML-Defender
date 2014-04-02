#include "../config.hpp"

#include <stdexcept>

#include "node.hpp"

/** \brief dtor
 */
Node::~Node()
{
}

/** \brief Get the first child (named by "name" if precised)
 *
 * \param name const std::string&
 * \return Node&
 *
 */
Node& Node::firstChild(const std::string& name)
{
    // If there is no name specified, returns the first node
    if(name == "")
        return *_children.front();

    // else, loop and return the first node with this name if it exists
    for(std::vector<Node*>::iterator itrChild = _children.begin() ; itrChild != _children.end() ; ++itrChild)
    {
        if((*itrChild)->getName() == name)
            return **itrChild;
    }

    // if there is no child with this "name", throws an exception
    throw std::runtime_error("No node found with this name : " + name);
}

/** \brief Get the first child value (named by "name" if precised)
 *
 * \param name const std::string&
 * \return std::string
 *
 */
std::string Node::firstChildValue(const std::string& name)
{
    return firstChild(name).getValue();
}

/** \brief
 *
 * \param name const std::string&
 * \return Node::Attribute&
 *
 */
Node::Attribute& Node::firstAttribute(const std::string& name)
{
    // If there is no name specified, returns the first attribute
    if(name == "")
        return *_attributes.front();

    // else, loop and return the first node with this name if it exists
    for(std::vector<Attribute*>::iterator itrAttr = _attributes.begin() ; itrAttr != _attributes.end() ; ++itrAttr)
    {
        if((*itrAttr)->name == name)
            return **itrAttr;
    }

    // if there is no child with this "name", throws an exception
    throw std::runtime_error("No attribute found with this name : " + name);
}

/** \brief Get the value of the first attribute
 *
 * \param name const std::string&
 * \return std::string
 *
 */
std::string Node::firstAttributeValue(const std::string& name)
{
    return firstAttribute(name).value;
}

/** \brief Return all the children matching the "name", all if empty string
 *
 * \param name const std::string&
 * \return std::vector<Node*>
 *
 */
std::vector<Node*> Node::getChildren(const std::string& name)
{
    // return all the children if there is no name
    if(name == "")
        return _children;

    // return just the nodes matching the "name"
    std::vector<Node*> response;
    for(std::vector<Node*>::iterator childItr = _children.begin() ; childItr != _children.end() ; ++childItr)
        if((*childItr)->getName() == name)
            response.push_back(*childItr);

    return response;
}

/** \brief Get the name of the node
 *
 * \return std::string
 *
 */
std::string Node::getName()
{
    return _name;
}

/** \brief Get the value of the node
 *
 * \return std::string
 *
 */
std::string Node::getValue()
{
    return _value;
}
