//
// Created by Matthijs on 9-6-2016.
//

#ifndef FAGAN_XML_HPP
#define FAGAN_XML_HPP

#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace r2d2 {

    namespace xml {

        //! @brief Node in the xml hierarchy storing data and other nodes.
        //!
        //!
        class XmlNode {
        public:
            //! @brief Creates a tag with the name "node".
            explicit XmlNode();

            //! @brief Creates a node with the given name.
            //!
            //! @param name Name for the node.
            explicit XmlNode(const std::string &name);

            virtual ~XmlNode() = default;

            //! @brief Adds the specified node as a child in the hierarchy.
            //!
            //! Adding a node which already exists in a hierarchy causes that
            //! node to be removed from said hierarchy.
            //!
            //! @param child Node to add to the hierarchy.
            //! @return Reference to the added child for chaining.
            XmlNode &add_child(std::unique_ptr<XmlNode> child);

            //! @brief Gets a reference to a modifiable string which represents
            //! the value of the given attribute.
            //!
            //! @param attribute The attribute to get the value from.
            //! @return The value matching the given attribute.
            std::string &get_attribute(const std::string &attribute);

            //! @brief Returns the string which represents the specified attribute.
            //!
            //! @param attribute The attribute to get the value from.
            //! @return The value matching the given attribute.
            const std::string &get_attribute(const std::string attribute) const;

            //! @brief Adds an attribute and assigns a value to it.
            //!
            //! If the attribute is already defined, this function won't have
            //! an effect.
            //!
            //! @param attribute Name of the attribute.
            //! @param value Value assigned to the attribute.
            void add_attribute(const std::string &attribute,
                               const std::string &value);

            void remove_attribute(const std::string attribute);

            //! @brief Returns the string representation of this node.
            //!
            //! The string representation of the xml node also includes all of
            //! its descendants.
            //!
            //! @param indent_level Number of indents in front of this tag.
            //! @return String representation of this xml node.
            std::string to_string(unsigned int indent_level = 0) const;

        private:
            std::string name;
            std::map<std::string, std::string> attributes;
            std::vector<std::unique_ptr<XmlNode>> children;
        };

        //! @brief Writes the node and hierarchy to the string.
        //! @param lhs Stream to write the xml node to.
        //! @param rhs Node to write to the stream.
        //! @return The stream passed by lhs.
        std::ostream &operator<<(std::ostream &lhs, const XmlNode &rhs);

        //! @brief A node where should only be one of per xml hierarchy.
        //!
        //!
        class XmlRoot final : public XmlNode {
            // Make it possible only for XmlDocument to instantiate this.
            friend class XmlDocument;

        private:
            explicit XmlRoot() = default;

            explicit XmlRoot(const std::string &name);
        };

        //! @brief
        //!
        class XmlDocument {
        public:
            XmlDocument();

            //! @brief Creates a new Xml which puts the given options in the
            //! header.
            //!
            //! Using an empty string causes the value to be omitted. More so in
            //! case of version, which results in the header not appearing.
            //! @param version Version of Xml used for the output file.
            //! @param encoding Encoding used to save the output file.
            //! @param standalone Whether the xml document is standalone.
            XmlDocument(const std::string &version,
                        const std::string &encoding,
                        const std::string &standalone);

            //! @brief Returns the string representation of this document.
            //!
            //! The string representation of the xml document consists of the
            //! header and the root node and is descendants.
            //!
            //! @param indent_level Number of indents in front of this tag.
            //! @return String representation of this xml node.
            std::string to_string() const;

            //! @brief
            //!
            //! @return
            XmlRoot &get_root();

            //! @brief
            //!
            //! @return
            const XmlRoot &get_root() const;

        private:
            XmlRoot root;
            std::string version;
            std::string encoding;
            std::string standalone;
        };

        std::ostream &operator<<(std::ostream &lhs, const XmlDocument &rhs);
    }
}

#endif //FAGAN_XML_HPP
