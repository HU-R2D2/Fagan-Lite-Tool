//
// Created by Ferdi on 10-May-16.
//

#include "../include/CommentStyle.hpp"

using namespace std;
CommentStyle::CommentStyle(XmlFileFormat& current_xml)  : BaseTest{current_xml} {

}
bool CommentStyle::inspect(const std::string & file_contents)  {
    // ToDo test has been rewritten and should be tested again!
    string errors;
    bool test_ran_successful = true;
    for (uint16_t i = 0; i < file_contents.size(); ++i) {
        // if /* OR */ found
        if(file_contents.find("/*") != file_contents.npos || file_contents.find("*/") != file_contents.npos)   {
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
    return test_ran_successful;
}
