//
// Created by fstoeltie on 4/19/16.
//

#include "../include/LineLength.hpp"
#include <iterator>
#include <sstream>
#include <iostream>


LineLength::LineLength(XmlFileFormat &current_xml) : BaseTest{current_xml} {

}

bool LineLength::inspect(const std::string &file_contents) {
    //ToDo run the linelength test in here.
    //ToDo For each line in the file, check the linelength.
    //ToDo if the linelength is greater than allowed,
    //ToDo save linenumber and linelength.
    //string xml_output = "<linelength";
    std::shared_ptr<XmlNode> node = std::shared_ptr<XmlNode>
            (new XmlNode("linelength"));

    std::string xml_output;
    std::string line;
    std::stringstream sstream1;
    sstream1.str(file_contents);
    std::vector<std::string> f_contents;
    while (std::getline(sstream1, line))
        f_contents.push_back(line);

    std::string linelength_errors;
    bool test_ran_successful = true;

    int error_counter = 0;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        if (f_contents[i].length() > max_line_length) {
            ++error_counter;
            //PROBLEM WITH COUNTING LENGTH,
            //TAB IS CONVERTED TO SPACE IN MOST IDE'S. NOT IN string.length()
            test_ran_successful = false;
            node->add_node_text("line= " + std::to_string(i + 1) + " length= " +
                                        std::to_string(f_contents[i].length()) + "\n");
        }
    }

    node->add_attribute("errors", std::to_string(error_counter));
    xml_output +=  " errors = \"" + std::to_string(error_counter) + "\">\n";
    if (test_ran_successful) {
        xml_output += "No linelength errors found in file\n";
        //ToDo test_is_valid has to be removed, old code
        test_is_valid = true; // default is false
    }

    if(error_counter > 0)  {
        current_xml.base_node->add_child_node(node);
    }
    return false;
}

