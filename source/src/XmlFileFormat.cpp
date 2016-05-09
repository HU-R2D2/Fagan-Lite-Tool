//
// Created by Ferdi on 09-May-16.
//

#include "../include/XmlFileFormat.hpp"
#include <iostream>
void XmlFileFormat::add_xml_data(std::string data, XML_DATA xml_data_type)  {
    std::cout << "adding xml data..." << std::endl;
    //ToDo Check for XML_DATA type and adjust current xml data about file to insert new data in the correct structure
    switch(xml_data_type)   {
        case XML_DATA::LINE_LENGTH:
            xml_data.push_back("\n<linelength>" + data + "\n</linelength>");
            break;
    }

}
const std::vector<std::string>& XmlFileFormat::get_xml_data()   {
    return xml_data;
}