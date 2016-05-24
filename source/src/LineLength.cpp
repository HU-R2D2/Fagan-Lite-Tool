//
// Created by fstoeltie on 4/19/16.
//

#include "../include/LineLength.hpp"
#include <iterator>
#include <sstream>
#include <iostream>
using namespace std;
/*LineLength::LineLength(XmlFileFormat& current_xml, string& f_contents) : BaseTest{current_xml}, f_content{f_contents}  {

}*/
LineLength::LineLength(XmlFileFormat& current_xml) : BaseTest{current_xml}  {

}
string LineLength::xml_formatted() {
    //ToDo format warnings as correct xml format
    //ToDo Discuss or decide what correct xml format is
    //ToDo decide whether this method should be removed or not!
    return std::string();
}
bool LineLength::inspect(const std::string & file_contents) {
    //ToDo run the linelength test in here. For each line in the file, check the linelength.
    //ToDo if the linelength is greater than allowed, save linenumber and linelength.

    string line;
    stringstream sstream1;
    sstream1.str(file_contents);
    vector<string> f_contents;
    while(std::getline(sstream1, line))
        f_contents.push_back(line);

    string linelength_errors;
    bool test_ran_successful = true;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        if(f_contents[i].length() > max_line_length)   {
            //PROBLEM WITH COUNTING LENGTH, TAB IS CONVERTED TO SPACE IN MOST IDE'S. NOT IN string.length()
            test_ran_successful = false;
            linelength_errors +="\tline= " + to_string(i + 1) + " length= " + to_string(f_contents[i].length()) + "\n";
        }
    }
    if(test_ran_successful) {
        string no_errors = "No linelength errors found in file\n";
        current_xml.add_xml_data(XML_DATA::LINE_LENGTH, no_errors);
        test_is_valid = true; // default is false
    }
    else    {
        current_xml.add_xml_data(XML_DATA::LINE_LENGTH, linelength_errors);
    }
    return false;
}