//
// Created by Ferdi on 09-May-16.
//

#include "../include/XmlFileFormat.hpp"

void XmlFileFormat::add_xml_data(std::string data, XML_DATA xml_data_type) {
    //ToDo Check for XML_DATA type and adjust current xml data about file to insert new data in the correct structure
    //ToDo fix tab indention in xml data (extra tab in each sub node)
    //ToDO Responsibility changed to inspections
    switch (xml_data_type) {
        case XML_DATA::BEGIN:
            xml_data.push_back("<file= " + data + ">");
            break;
        case XML_DATA::END:
            xml_data.push_back("</file>\n");
            break;
        case XML_DATA::DOXYGEN:
            xml_data.push_back(data + "</doxygen>\n");
            break;
        case XML_DATA::DEFAULT:
            xml_data.push_back(data);
            break;
        case XML_DATA::INCLUSION_GUARD:
            xml_data.push_back(
                    "<inclusion-guard>\n" + data + "</inclusion-guard>");
            break;
        case XML_DATA::INDENTATION:
            xml_data.push_back("<indentation>\n" + data + "</indentation>\n");
            break;
    }
}
const std::string XmlFileFormat::data()  {
    return base_node->get_all_nodes_data();
}
const std::vector<std::string> &XmlFileFormat::get_xml_data() {
    return xml_data;
}

XmlFileFormat::XmlFileFormat() : base_node{new XmlNode("root")}{

}
