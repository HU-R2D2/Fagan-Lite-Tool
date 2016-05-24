//
// Created by fstoeltie on 4/19/16.
//

#ifndef FAGAN_LINELENGTH_HPP
#define FAGAN_LINELENGTH_HPP
#include <string>
//#include <map>
#include <vector>
#include "Test_Type.hpp"
#include "BaseTest.hpp"
class LineLength : public BaseTest{
public:
    //LineLength(XmlFileFormat& current_xml, std::string& f_contents);
    LineLength(XmlFileFormat& current_xml);
    std::string xml_formatted();
    bool inspect(const std::string & file_contents) override;
    bool inspect_and_fix(std::string & file_contents){return false;}
private:
    //std::string& f_content;
    //Test_Type TT;
    const uint8_t max_line_length = 80;
    //std::map< uint16_t, uint16_t  > invalid_line_lengths;
};


#endif //FAGAN_LINELENGTH_HPP
