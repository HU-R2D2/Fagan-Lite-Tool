//
// Created by Ferdi on 09-May-16.
//

#include "../include/XmlFileFormat.hpp"
void XmlFileFormat::add_xml_data(std::string data, XML_DATA xml_data_type)  {
    //ToDo Check for XML_DATA type and adjust current xml data about file to insert new data in the correct structure
    xml_data.push_back(data);
}