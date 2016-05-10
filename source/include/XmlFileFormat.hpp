//
// Created by Ferdi on 09-May-16.
//

#ifndef FAGAN_XMLFILEFORMAT_HPP
#define FAGAN_XMLFILEFORMAT_HPP

#include <string>
#include <vector>
enum class XML_DATA{
    BEGIN,
    END,
    LINE_LENGTH
};
class XmlFileFormat {
public:
    void add_xml_data(XML_DATA xml_data_type, std::string data = "");
    const std::vector<std::string>& get_xml_data();
private:
    std::vector<std::string> xml_data;
};


#endif //FAGAN_XMLFILEFORMAT_HPP
