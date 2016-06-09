//
// Created by Ferdi on 08-Jun-16.
//

#ifndef FAGAN_XmlNode_HPP
#define FAGAN_XmlNode_HPP
#include <vector>
#include <memory>

class XmlNode : public std::enable_shared_from_this<XmlNode> {
public:
    //ToDo tree cannot be removed, should have a clear method.
    XmlNode(std::string xml_node_name, std::string node_value);
    XmlNode(std::shared_ptr<XmlNode> parent) :
            parent{parent}  {
    }
    void fix(std::string xml_node_name, std::string node_value = "")  {
        parent->add_child_node(shared_from_this());
        set_indentation_depth();
        add_node_name(xml_node_name, node_value);
    }
    void initialize()   {
        parent->add_child_node(shared_from_this());
        set_indentation_depth();
    }
    void add_child_node(std::shared_ptr<XmlNode> child) {
        children.push_back(child);
    }
    void add_attribute(std::string attribute, std::string attribute_value)   {
        begin = begin.substr(0, begin.size() - 2);  // remove closing ">" @ node
        begin += " " + attribute + "=" + "\"" + attribute_value + "\">\n";
    }
    void add_node_name(std::string node_name, std::string value = "")   {
        std::string temp;
        if(!value.empty())  {
            temp  = "=\"" + value + "\"";
        }
        begin   += node_indentation + "<" + node_name + "" + temp + ">\n";
        end     += node_indentation + "</" + node_name + ">\n";
    }
    void add_node_text(std::string text)    {
        node_text += node_indentation + "\t" + text;
    }
    int calculate_node_depth() {
        if(parent)    {
            return node_depth += parent->calculate_node_depth() + 1;
        }
        return node_depth;
    }
    void set_indentation_depth()   {
        uint8_t n_depth = calculate_node_depth();
        while(n_depth--) {
            node_indentation += "\t";
        }
    }


    void clear_node()   {
        for(auto child : children)  {
            child->clear_node();
        }
        for (std::vector<std::shared_ptr<XmlNode>>::iterator it = parent->children.begin(); it != parent->children.end();)   {
            if(it->get() == this)   {
                it->reset();
                parent->children.erase(it);
            }
            else    {
                ++it;
            }
        }
    }
    std::string get_all_nodes_data()    {
        std::string xml_data = begin;
        xml_data += node_text;
        for(auto child : children)  {
            xml_data += child->get_all_nodes_data();
        }
        xml_data += end;
        return xml_data;
    }
private:
    std::string node_indentation;
    std::string begin, end;
    std::string node_text;
    std::string node_name;
    uint8_t node_depth = 0;
    std::shared_ptr<XmlNode> parent;
    std::vector<std::shared_ptr<XmlNode>> children;

};


#endif //FAGAN_XmlNode_HPP
