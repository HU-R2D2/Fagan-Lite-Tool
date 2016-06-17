//! \addtogroup 24 Fagan lite tool
//!
//! \file   DoxygenCheck.hpp
//! \author Ferdi Stoelti
//! \date   17-06-16
//! \brief  Utility for creating xml structures.
//!
//! \copyright Copyright © 2016, HU University of Applied Sciences Utrecht.
//! All rights reserved.
//!
//! License: newBSD
//!
//! Redistribution and use in source and binary forms,
//! with or without modification, are permitted provided that
//! the following conditions are met:
//! - Redistributions of source code must retain the above copyright notice,
//!   this list of conditions and the following disclaimer.
//! - Redistributions in binary form must reproduce the above copyright notice,
//!   this list of conditions and the following disclaimer in the documentation
//!   and/or other materials provided with the distribution.
//! - Neither the name of the HU University of Applied Sciences Utrecht
//!   nor the names of its contributors may be used to endorse or promote
//!   products derived from this software without specific prior written
//!   permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//! "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
//! BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
//! AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//! IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
//! BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//! OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//! WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//! OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//! EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ~< HEADER_VERSION 2016 04 12 >~

#include "../include/XmlNode.hpp"

XmlNode::XmlNode(std::string xml_node_name, std::string node_value)  {

    add_node_name(xml_node_name, node_value);
    node_data.node_depth = 0;
}

void XmlNode::add_child_node(std::shared_ptr<XmlNode> child) {
    child->set_parent(shared_from_this());
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
    node_data.begin   += "<" + node_name + "" + temp + ">\n";
    node_data.end     += "</" + node_name + ">\n";
}
void XmlNode::add_node_text(std::string text)    {
    node_data.node_text.push_back(text);
}
int XmlNode::calculate_node_depth() {
    int indent = 0;
    auto ancestor = parent.lock();
    while(ancestor) {
        ancestor = ancestor->parent.lock();
        ++indent;
    }
    return indent;
}
void XmlNode::set_indentation_depth()   {
    uint8_t n_depth = calculate_node_depth();
    node_data.node_indentation = "";
    while(n_depth--) {
        node_data.node_indentation += "\t";
    }
    for(auto ch : children) {
        ch->set_indentation_depth();
    }
}
//ToDo method should be renamed to clear_node and clear_node has to be renamed to something else.
void XmlNode::clear_node_data()   {
    for(auto child : children)  {
        child->clear_node_data();
        child->node_data.node_indentation = child->node_data.node_depth = 0;
        child->node_data.begin = child->node_data.end = "";
        child->node_data.node_text.clear();
    }
    node_data. node_indentation = node_data.node_depth = 0;
    node_data.begin = node_data.end;
    node_data.node_text.clear();
}

std::string XmlNode::get_all_nodes_data()    {
    set_indentation_depth();
    std::string xml_data = node_data.node_indentation + node_data.begin;
    for(auto str : node_data.node_text) {
        xml_data += node_data.node_indentation + "\t" + str;
    }
    for(auto child : children)  {
        xml_data += child->get_all_nodes_data();
    }

    xml_data += node_data.node_indentation + node_data.end;
    return xml_data;
}

void XmlNode::set_parent(std::weak_ptr<XmlNode> p) {
    this->parent = p;
}