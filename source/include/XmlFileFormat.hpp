//
// Created by Ferdi on 09-May-16.
//

#ifndef FAGAN_XMLFILEFORMAT_HPP
#define FAGAN_XMLFILEFORMAT_HPP

#include <string>
#include <vector>
class XmlFileFormat {
public:
    void add_xml_data(std::string data, XML_DATA xml_data_type);
private:
    std::vector<std::string> xml_data;
};
enum class XML_DATA{

};

#endif //FAGAN_XMLFILEFORMAT_HPP
