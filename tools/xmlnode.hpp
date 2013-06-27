#ifndef XMLNODE_HPP
#define XMLNODE_HPP

/** \brief Proxy for rapidxml to use easily and properly in the game
 */
class XMLNode : public Node
{
    public:
        XMLNode();
        XMLNode(const XMLNode* parent);
        ~XMLNode();

        void loadFromFile(const std::string& filename);
        void parse(rapidxml::xml_node<>* node);

    private:
        const XMLNode* _parent;
};

#endif // XMLNODE_HPP
