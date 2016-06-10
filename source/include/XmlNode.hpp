//
// Created by Ferdi on 08-Jun-16.
//

#ifndef FAGAN_XmlNode_HPP
#define FAGAN_XmlNode_HPP
#include <string>
#include <vector>
#include <memory>
#include <iostream>
struct XmlData{
    std::string node_indentation;
    std::string begin, end;
    std::string node_text;
    uint8_t node_depth = 0;
};
class XmlNode : public std::enable_shared_from_this<XmlNode> {
public:

    XmlNode(std::string xml_node_name, std::string node_value = "");
    XmlNode(std::shared_ptr<XmlNode> parent);

    void initialize();

    void add_child_node(std::shared_ptr<XmlNode> child);
    void add_attribute(std::string attribute, std::string attribute_value);
    void add_node_name(std::string node_name, std::string value = "");
    void add_node_text(std::string text);

    //ToDo method should be renamed to clear_node and clear_node has to be renamed to something else.
    void clear_node_data();
    std::string get_all_nodes_data();
private:
    int calculate_node_depth();
    void set_indentation_depth();
    void set_parent(std::weak_ptr<XmlNode>);
    XmlData node_data;
    std::weak_ptr<XmlNode> parent;
    std::vector<std::shared_ptr<XmlNode>> children;

};


#endif //FAGAN_XmlNode_HPP
