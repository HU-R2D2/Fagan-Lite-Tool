//
// Created by Ferdi on 11-May-16.
//

#include <iostream>
#include <sstream>
#include "../include/InclusionGuards.hpp"

using namespace std;

InclusionGuards::InclusionGuards(XmlFileFormat &current_xml) : BaseTest{
        current_xml} {

}

bool InclusionGuards::inspect(const std::string &file_contents) {
    //ToDo change test and fix
    const string inspection_name = "inclusion-guards";
    string xml_output = "<" + inspection_name;

    string line;
    stringstream sstream1;
    sstream1.str(file_contents);
    vector<string> f_contents;
    while (std::getline(sstream1, line))
        f_contents.push_back(line);


    bool test_ran_successful = true;
    bool ifndef = false;
    bool define = false;
    bool endif = false;

    int error_counter = 0;
    for (uint16_t i = 0; i < f_contents.size(); i++) {
        if (!ifndef && f_contents[i].find("#ifndef") != f_contents[i].npos) {
            ifndef = true;
        }
        else if (ifndef && !define &&
                 f_contents[i].find("#define") != f_contents[i].npos) {
            // ifndef comes before includes
            define = true;
        }
        else if ((f_contents[i].find("#include") ||
                  f_contents[i].find("class") ||
                  f_contents[i].find("struct") ||
                  f_contents[i].find("enum")) && !define) {
            test_ran_successful = false;
            ++error_counter;
            break;

        }

    }
    if (define && !endif && (f_contents[f_contents.size() - 1].find("#endif") !=
                             f_contents[f_contents.size() - 1].npos ||
                             f_contents[f_contents.size() - 2].find("#endif") !=
                             f_contents[f_contents.size() - 2].npos)) {
        endif = true;
    }
    else {
        test_is_valid = false;
    }
    xml_output +=  " errors = \"" + to_string(error_counter) + "\">\n";
    if (test_ran_successful) {
        string no_errors = "No Inclusion Guard errors found in file\n";
        current_xml.add_xml_data(no_errors);
        test_is_valid = true; // default is false
    }
    else {
        if (!ifndef) {
            xml_output += "\tInvalid ifndef found for Inclusion Guard!\n";

        }
        else if (!define) {
            xml_output +=  "\tInvalid define found for Inclusion Guard!\n";
        }
        else if (!endif) {
            xml_output = "\tInvalid endif found for Inclusion Guard!\n";
        }
    }
    xml_output += "</" + inspection_name + ">\n";
    current_xml.add_xml_data(xml_output);
    return test_ran_successful;
}