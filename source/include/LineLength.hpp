//
// Created by fstoeltie on 4/19/16.
//

#ifndef FAGAN_LINELENGTH_HPP
#define FAGAN_LINELENGTH_HPP
#include <string>
#include "Test_Type.hpp"
#include <map>
class LineLength {
public:
    LineLength(std::string& f_contents, Test_Type TT);
    std::string xml_formatted();
private:
    std::string& f_content;
    Test_Type TT;
    const uint8_t max_line_length = 80;
    std::map< uint16_t, uint16_t  > invalid_line_lengths;
};


#endif //FAGAN_LINELENGTH_HPP
