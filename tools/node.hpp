#ifndef NODE_HPP
#define NODE_HPP

/** \brief Abstract proxy class for parsing languages used in the game
 */
class Node
{
    public:

        struct Attribute
        {
            std::string name;
            std::string value;
        };

        virtual ~Node();

        virtual void loadFromFile(const std::string& filename) = 0; // inherit the class and override this function

        virtual Node& firstChild(const std::string& name = "");
        virtual std::string firstChildValue(const std::string& name = "");

        virtual Attribute& firstAttribute(const std::string& name = "");
        virtual std::string firstAttributeValue(const std::string& name = "");

        virtual std::string getName();
        virtual std::string getValue();

    protected:

        const Node* _parent;

        std::vector<Attribute*> _attributes;
        std::vector<Node*> _children;

        std::string _name;
        std::string _value;

        std::string _filename;
};

#endif // NODE_HPP
