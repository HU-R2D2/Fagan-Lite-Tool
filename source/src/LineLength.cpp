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
LineLength::LineLength(XmlFileFormat &current_xml) : BaseTest{current_xml} {

}

bool LineLength::inspect(const std::string &file_contents) {
    //ToDo run the linelength test in here. For each line in the file, check the linelength.
    //ToDo if the linelength is greater than allowed, save linenumber and linelength.
    //string xml_output = "<linelength";
    std::shared_ptr<XmlNode> node = std::shared_ptr<XmlNode>(new XmlNode(current_xml.base_node));
    node->initialize();
    node->add_node_name("linelength");
    string xml_output;
    string line;
    stringstream sstream1;
    sstream1.str(file_contents);
    vector<string> f_contents;
    while (std::getline(sstream1, line))
        f_contents.push_back(line);

    string linelength_errors;
    bool test_ran_successful = true;

    int error_counter = 0;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        if (f_contents[i].length() > max_line_length) {
            ++error_counter;
            //PROBLEM WITH COUNTING LENGTH, TAB IS CONVERTED TO SPACE IN MOST IDE'S. NOT IN string.length()
            test_ran_successful = false;
            node->add_node_text("line= " + to_string(i + 1) + " length= " +
                                to_string(f_contents[i].length()) + "\n");
        }
    }

    if(error_counter == 0)  {

        node->clear_node_data();
    }
    node->add_attribute("errors", to_string(error_counter));
    xml_output +=  " errors = \"" + to_string(error_counter) + "\">\n";
    if (test_ran_successful) {
        xml_output += "No linelength errors found in file\n";
        //ToDo test_is_valid has to be removed, old code
        test_is_valid = true; // default is false
    }
    current_xml.add_xml_data(xml_output);
    return false;
}