//
// Created by Ferdi on 10-May-16.
//

#include <sstream>
#include "../include/CommentStyle.hpp"

using namespace std;
CommentStyle::CommentStyle(XmlFileFormat& current_xml)  : BaseTest{current_xml} {

}
bool CommentStyle::inspect(const std::string & file_contents)  {
    // ToDo test has been rewritten and should be tested again!
    string errors;
    string line;
    stringstream sstream1;
    sstream1.str(file_contents);
    vector<string> f_contents;
    bool isWrongCommentBlock = false;
    while(std::getline(sstream1, line))
        f_contents.push_back(line);

    bool test_ran_successful = true;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        // If /* has been found, set line it is found on as start of wrong comment block
        if(f_contents[i].find("/*") != f_contents[i].npos)   {
            test_ran_successful = false;    // Current inspection ran with failures
            isWrongCommentBlock = true;     // Wrong comment block detected, set bool to true to also search for endline
            errors += "\tWrong comment style found, started at line = " + to_string(i + 1) + "\n";
        }
        // Else if */ has been found, set line it is found on as end of comment block
        else if(isWrongCommentBlock && f_contents[i].find("*/") != f_contents[i].npos) {
            errors += "\tWrong comment style ended at line =  " + to_string(i + 1) + "\n";
        }
    }
    if(test_ran_successful) {
        string no_errors = "\tNo comment style errors found in file\n";
        current_xml.add_xml_data(XML_DATA::COMMENT_STYLE, no_errors);
        test_is_valid = true; // default is false
    }
    else    {
        current_xml.add_xml_data(XML_DATA::COMMENT_STYLE, errors);
    }
    return test_ran_successful;
}
