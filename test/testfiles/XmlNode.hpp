//! \addtogroup 24 Fagan lite tool

//! \file   DoxygenCheck.hpp
//! \author Ferdi Stoeltie
//! \date   06-10-16
//! \brief  Utility for helping create an xml file with the found issues.
//!
//! \copyright Copyright � 2016, HU University of Applied Sciences Utrecht.
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

#ifndef FAGAN_XmlNode_HPP
#define FAGAN_XmlNode_HPP
#include <string>
#include <vector>
#include <memory>
#include <iostream>

//! \brief Simple XmlData struct, that contains the raw data within an xml node.
struct XmlData{
    std::string node_indentation;
    std::string begin, end;
    std::vector<std::string> node_text;
    uint8_t node_depth = 0;
};

//@brief Contains xml data and can be linked to other xml nodes to form an xml tree.
class XmlNode : public std::enable_shared_from_this<XmlNode> {
public:
    //! @brief Constructs a XmlNode with a node name and the node name value.
    //! @param xml_node_name Name of this node.
    //! @param xml_node_name value of this node name.
    XmlNode(std::string xml_node_name, std::string node_value = "");

    //! @brief Adds a node as a child node to the current node.
    //! @param std::shared_ptr<XmlNode> child Pointer to the child node.
    void add_child_node(std::shared_ptr<XmlNode> child);

    //! @brief Adds text to the node.
    //! @param std::string text Text to be added.
    void add_node_text(std::string text);
    //! @brief Adds an attribute and a linked value to the current node.
    //! @param std::string attribute The attribute name.
    //! @param std::string attribute_value The attribute value.
    void add_attribute(std::string attribute, std::string attribute_value);

    //ToDo method should be renamed to clear_node and clear_node has to be renamed to something else.
    //! @brief Clears all the node data and the data of its subsequent childs aswell.
    void clear_node_data();

    //! @brief Returns all XML data within the XML node tree.
    //! @return std::string Containing all XML data.
    std::string get_all_nodes_data();
private:
    int calculate_node_depth();
    void set_indentation_depth();
    void set_parent(std::weak_ptr<XmlNode>);
    void add_node_name(std::string xml_node_name, std::string node_value = "");

    XmlData node_data;
    std::weak_ptr<XmlNode> parent;
    std::vector<std::shared_ptr<XmlNode>> children;

};
#endif //FAGAN_XmlNode_HPP
