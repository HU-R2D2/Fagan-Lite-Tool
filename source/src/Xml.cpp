//
// Created by Matthijs on 9-6-2016.
//

#include "../include/Xml.hpp"
#include <sstream>
#include <string>

namespace r2d2 {

    namespace xml {

        XmlNode::XmlNode() : name{"node"} {

        }

        XmlNode::XmlNode(const std::string &name) : name{name} {

        }

        XmlNode & XmlNode::add_child(std::unique_ptr<XmlNode> child) {
            children.push_back(std::move(child));
            return *((children.end()-1)->get());
        }

        std::string XmlNode::to_string(unsigned int indent_level) const {
            // Specifies which character should be used for an indent,
            // and how often this character should be repeated per indent.
            // TODO: Determine whether this needs a global setting for runtime.
            constexpr char indent_character = ' ';
            constexpr size_t repeat = 4;

            indent_level *= repeat;

            std::ostringstream stream{""};
            // Start the creation of the opening tag.
            // Spacing is at the end so the attributes don't get concatenated.
            stream << std::string(indent_level, indent_character);
            stream << "<" << name;

            for (const auto &attribute : attributes) {
                stream << " " << attribute.first << "=\"" << attribute.second << "\"";
            }

            // An 'empty' xml tag is typically put on one line, requiring a
            // different closing method. Determine which style is relevant.
            if (children.size()) {
                // Multi-line tag.
                stream << ">" << std::endl;
                for (const auto &child : children) {
                    if (child) {
                        // Child tags typically appear between the opening and
                        // closing tag at a higher indent level.
                        stream << child->to_string(indent_level + 1);
                    }
                }
                // Add the closing tag at the correct level of indentation.
                stream << std::string(indent_level * repeat, indent_character);
                stream << "</" << name << ">" << std::endl;
            } else {

                stream << "/>" << std::endl;
            }
            return stream.str();
        }

        std::ostream &operator<<(std::ostream &lhs, const XmlNode &rhs) {
            return lhs << rhs.to_string();
        }

        XmlRoot::XmlRoot(const std::string &name) : XmlNode{name} {

        }

        XmlDocument::XmlDocument() : root{"root"} {

        }

        XmlDocument::XmlDocument(
                const std::string &version,
                const std::string &encoding,
                const std::string &standalone) : root{"root"},
                                                 version{version},
                                                 encoding{encoding},
                                                 standalone{standalone} {

        }

        std::string XmlDocument::to_string() const {
            std::ostringstream stream{""};

            // A header is not mandatory, but a version must be specified
            // when a header is present.
            if (version != "") {
                stream << "<?xml";
                stream << " version=\"" << version << "\"";

                // The header should be specified in the order
                // version(, encoding)(, standalone). Of which the latter
                // two are optional.
                if (encoding != "") {
                    stream << " encoding=\"" << encoding << "\"";
                }
                if (standalone != "") {
                    stream << " standalone=\"" << standalone << "\"";
                }
                // Close the header as to not confuse other programs.
                stream << "?>" << std::endl;
            }
            stream << root.to_string();
            return stream.str();
        }

        std::ostream &operator<<(std::ostream &lhs, const XmlDocument &rhs) {
            return lhs << rhs.to_string();
        }

        XmlRoot &XmlDocument::get_root() {
            return root;
        }

        const XmlRoot &XmlDocument::get_root() const {
            return root;
        }

        std::string & XmlNode::get_attribute(const std::string &attribute) {
            return attributes[attribute];
        }

        const std::string & XmlNode::get_attribute(
                const std::string attribute) const {

            return attributes.at(attribute);
        }

        void XmlNode::add_attribute(const std::string &attribute,
                                    const std::string &value) {
            attributes.insert(std::make_pair(attribute, value));
        }

        void XmlNode::remove_attribute(const std::string attribute) {

        }

    }
}