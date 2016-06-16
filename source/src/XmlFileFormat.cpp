#include "../include/XmlFileFormat.hpp"

XmlFileFormat::XmlFileFormat() : base_node{new XmlNode("root")}{

}

const std::string XmlFileFormat::data()  {
    return base_node->get_all_nodes_data();
}
/*const std::vector<std::string> &XmlFileFormat::get_xml_data() {
    return xml_data;
}*/


