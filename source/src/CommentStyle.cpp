//
// Created by Ferdi on 10-May-16.
//

#include "../include/CommentStyle.hpp"

using namespace std;
CommenStyle::CommenStyle(XmlFileFormat& current_xml, std::vector<std::string> & f_contents)  : BaseTest{current_xml}, f_contents{f_contents}  {

}
void CommenStyle::inspect()  {
    string errors;
    bool test_ran_successful = true;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        // if /* OR */ found
        if(f_contents[i].find("/*") != f_contents[i].npos || f_contents[i].find("*/") != f_contents[i].npos)   {
            test_ran_successful = false;
            errors += "\tline= " + to_string(i + 1) + " wrong comment style found\n";
        }
    }
    if(test_ran_successful) {
        string no_errors = "\tNo comment style errors found in file\n";
        current_xml.add_xml_data(XML_DATA::COMMENT_STYLE, no_errors);
        test_is_valid = true; // default is false
    }
    else    {
        current_xml.add_xml_data(XML_DATA::LINE_LENGTH, errors);
    }
}
