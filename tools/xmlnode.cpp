#include "../config.hpp"

#include "../tools/rapidxml/rapidxml.hpp"
#include "../tools/rapidxml/rapidxml_utils.hpp"

#include "node.hpp"
#include "xmlnode.hpp"

/** \brief ctor
 */
XMLNode::XMLNode()
{
}

/** \brief ctor with the parent parameter
 *
 * \param parent const XMLNode*
 *
 */
XMLNode::XMLNode(const XMLNode* parent) : _parent(parent)
{
}

/** \brief Erase the attributes and the children allocated during the parsing
 */
XMLNode::~XMLNode()
{
    std::for_each(_attributes.begin(), _attributes.end(), Deallocator<Attribute>());
    std::for_each(_children.begin(), _children.end(), Deallocator<Node>());
}

/** \brief Load a XMLNode from a file with rapidxml
 *
 * \param filename const std::string&
 * \return void
 *
 */
void XMLNode::loadFromFile(const std::string& filename)
{
    try
    {
        rapidxml::file<> file(filename.c_str());
        rapidxml::xml_document<> document;
        document.parse<0>(file.data());

        parse(document.first_node());
    }
    catch(std::exception const& e)
    {
        // Logger class please !
        std::cerr << "Error : " << e.what() << std::endl;
    }
}

/** \brief Parse a document from a root rapidxml node
 *
 * \param node rapidxml::xml_node<>*
 * \return void
 *
 */
void XMLNode::parse(rapidxml::xml_node<>* node)
{
    _name = node->name();
    _value = node->value();

    // Fills the attributes
    rapidxml::xml_attribute<>* attr = node->first_attribute();
    while(attr != NULL)
    {
        Node::Attribute* a = new Node::Attribute();
        a->name = attr->name();
        a->value = attr->value();
        _attributes.push_back(a);

        attr = attr->next_attribute();
    }

    // Let's see the children of this node
    node = node->first_node();

    while(node != NULL)
    {
        // Creates a node and we fill it
        XMLNode* child = new XMLNode(this);
        child->parse(node);
        _children.push_back(child); // We fill the std::vector with the children

        node = node->next_sibling();
    }
}
