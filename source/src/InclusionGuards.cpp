//
// Created by Ferdi on 11-May-16.
//

#include <iostream>
#include "../include/InclusionGuards.hpp"
using namespace std;
InclusionGuards::InclusionGuards(XmlFileFormat& current_xml, std::vector<std::string> & f_contents) : BaseTest{current_xml}, f_contents{f_contents} {

}
void InclusionGuards::inspect() {

    bool test_ran_successful = true;
    bool ifndef = false;
    bool define = false;
    bool endif = false;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        if(f_contents[i].find("#ifndef") && !ifndef)    {
            // ifndef comes before includes
            ifndef = true;
        }
        else if(f_contents[i].find("#define") && ifndef)    {
            // ifndef comes before includes
            define = true;
        }
        else if(   (f_contents[i].find("#include")  ||
                    f_contents[i].find("class")     ||
                    f_contents[i].find("struct")    ||
                    f_contents[i].find("enum"))      && !define) {
            cout << "gotten to this stage already...\n\n\n";
            test_ran_successful = false;
            break;

        }
        else if(f_contents[i].find("#endif") && define && (i == f_contents.size() || i == f_contents.size() - 1)) {
            endif = true;

        }
        else    {
            test_ran_successful = false;
        }

    }
    if(test_ran_successful) {
        string no_errors = "No Inclusion Guard errors found in file\n";
        current_xml.add_xml_data(XML_DATA::LINE_LENGTH, no_errors);
        test_is_valid = true; // default is false
    }
    else    {
        if(ifndef)  {
            current_xml.add_xml_data(XML_DATA::INCLUSION_GUARD, "\tInvalid ifndef found for Inclusion Guard!\n");
        }
        else if(define)  {
            current_xml.add_xml_data(XML_DATA::INCLUSION_GUARD, "\tInvalid define found for Inclusion Guard!\n");
        }
        else if(endif)  {
            current_xml.add_xml_data(XML_DATA::INCLUSION_GUARD, "\tInvalid endif found for Inclusion Guard!\n");
        }
    }
}