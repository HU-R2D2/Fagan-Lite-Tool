//
// Created by Ferdi on 08-Jun-16.
//

#include "../include/XmlNode.hpp"
XmlNode::XmlNode(std::string xml_node_name, std::string node_value)  {
    add_node_name(xml_node_name, node_value);
    node_depth = 0;
}