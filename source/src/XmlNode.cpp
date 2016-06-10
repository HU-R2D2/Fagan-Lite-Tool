//
// Created by Ferdi on 08-Jun-16.
//

#include "../include/XmlNode.hpp"

XmlNode::XmlNode(std::string xml_node_name, std::string node_value)  {
    add_node_name(xml_node_name, node_value);
    node_data.node_depth = 0;
}

XmlNode::XmlNode(std::shared_ptr<XmlNode> parent) :
parent{parent}  {}

void XmlNode::initialize()   {
    std::shared_ptr<XmlNode> p = parent.lock();
    if(p)   {
        p->add_child_node(shared_from_this());
    }
    set_indentation_depth();
}
void XmlNode::add_child_node(std::shared_ptr<XmlNode> child) {
    children.push_back(child);
}
void XmlNode::add_attribute(std::string attribute, std::string attribute_value)   {
    node_data.begin = node_data.begin.substr(0, node_data.begin.size() - 2);  // remove closing ">" @ node
    node_data.begin += " " + attribute + "=" + "\"" + attribute_value + "\">\n";
}
void XmlNode::add_node_name(std::string node_name, std::string value)   {
    std::string temp;
    if(!value.empty())  {
        temp  = "=\"" + value + "\"";
    }
    node_data.begin   += node_data.node_indentation + "<" + node_name + "" + temp + ">\n";
    node_data.end     += node_data.node_indentation + "</" + node_name + ">\n";
}
void XmlNode::add_node_text(std::string text)    {
    node_data.node_text += node_data.node_indentation + "\t" + text;
}
int XmlNode::calculate_node_depth() {
    std::shared_ptr<XmlNode> p = parent.lock();
    if(p)    {
        return node_data.node_depth += p->calculate_node_depth() + 1;
    }
    return node_data.node_depth;
}
void XmlNode::set_indentation_depth()   {
    uint8_t n_depth = calculate_node_depth();
    while(n_depth--) {
        node_data.node_indentation += "\t";
    }
}
//ToDo method should be renamed to clear_node and clear_node has to be renamed to something else.
void XmlNode::clear_node_data()   {
    for(auto child : children)  {
        child->clear_node_data();
        child->node_data.node_indentation = child->node_data.node_depth = 0;
        child->node_data.begin = child->node_data.end = child->node_data.node_text = "";
    }
    node_data. node_indentation = node_data.node_depth = 0;
    node_data.begin = node_data.end = node_data.node_text = "";
}

std::string XmlNode::get_all_nodes_data()    {
    std::string xml_data = node_data.begin;
    xml_data += node_data.node_text;
    for(auto child : children)  {
        xml_data += child->get_all_nodes_data();
    }
    xml_data += node_data.end;
    return xml_data;
}