//
// Created by fstoeltie on 4/19/16.
//

#include "../include/LineLength.hpp"
#include <iterator>
#include <sstream>
#include <iostream>
using namespace std;
LineLength::LineLength(XmlFileFormat& current_xml, string& f_contents) : BaseTest{current_xml}, f_content{f_contents}  {

}
string LineLength::xml_formatted() {
    //ToDo format warnings as correct xml format
    //ToDo Discuss or decide what correct xml format is
    return std::string();
}
void LineLength::inspect() {
    //ToDo run the linelength test in here. For each line in the file, check the linelength.
    //ToDo if the linelength is greater than allowed, save linenumber and linelength.
    string linelength_errors;
    istringstream iss(f_content);
    bool test_ran_successful = false;
    cout << "getting f_content" << endl;
    cout << f_content << endl;
    vector<string> strings{istream_iterator<string>{iss},
                           istream_iterator<string>{}};
    for (uint16_t i = 0; i < strings.size(); ++i) {
        if(strings[i].length() > max_line_length)   {
            test_ran_successful = true;
            linelength_errors +="line= " + to_string(i) + " length= " + to_string(strings[i].length()) + "\n";
        }
    }
    if(test_ran_successful) {
        string no_errors = "No linelength test errors found in file\n";
        current_xml.add_xml_data(no_errors, XML_DATA::LINE_LENGTH);
        test_failed = false; // default is true
    }
    else    {
        current_xml.add_xml_data(linelength_errors, XML_DATA::LINE_LENGTH);
    }


}