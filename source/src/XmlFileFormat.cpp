//
// Created by Ferdi on 09-May-16.
//

#include "../include/XmlFileFormat.hpp"
#include <iostream>
void XmlFileFormat::add_xml_data(XML_DATA xml_data_type, std::string data)  {
    //ToDo Check for XML_DATA type and adjust current xml data about file to insert new data in the correct structure
    //ToDo fix tab indention in xml data (extra tab in each sub node)
    switch(xml_data_type)   {
        case XML_DATA::BEGIN:
            xml_data.push_back("<file= " + data + ">");
            break;
        case XML_DATA::END:
            xml_data.push_back("</file>\n");
            break;
        case XML_DATA::LINE_LENGTH:
            xml_data.push_back("<linelength>\n" + data + "</linelength>");
            break;
    }

}
const std::vector<std::string>& XmlFileFormat::get_xml_data()   {
    return xml_data;
}