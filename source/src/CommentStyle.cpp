//
// Created by Ferdi on 10-May-16.
//

#include <sstream>
#include "../include/CommentStyle.hpp"
#include <regex>
using namespace std;
CommentStyle::CommentStyle(XmlFileFormat& current_xml)  : BaseTest{current_xml} {

}
bool CommentStyle::inspect(const std::string & file_contents)  {
    //ToDo test has been rewritten and should be tested again!
    //ToDo change stuff to base inspector class, such as xml output and inspection name, also logic etc.

    std::shared_ptr<XmlNode> node = std::shared_ptr<XmlNode>(new XmlNode("comment-style"));
    //const string inspection_name = "comment-style";
    //string xml_output = "<" + inspection_name;

    string errors;
    string line;
    stringstream sstream1;
    sstream1.str(file_contents);
    vector<string> f_contents;
    bool can_check = true;
    bool isWrongCommentBlock = false;

    while(std::getline(sstream1, line))
        f_contents.push_back(line);

    bool test_ran_successful = true;
    // (\w+\s*[\*\&]*(::)?([=+-><]?){0,2}\s*){1,3}[(](\w+\s*[\*\&]*\s*\w*(\s*([,]\s*\w+\s*[\*\&]*\s*\w+)*))?[)]
    int error_counter = 0;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        if(f_contents[i].find("\"") != f_contents[i].npos)  {
            can_check = !can_check;
        }
        if(can_check)    {
            // If /* has been found, set line it is found on as start of wrong comment block
            if(f_contents[i].find("/*") != f_contents[i].npos)   {
                ++error_counter;
                test_ran_successful = false;    // Current inspection ran with failures
                isWrongCommentBlock = true;     // Wrong comment block detected, set bool to true to also search for endline
                node->add_node_text("Wrong comment style found, started at line = " + to_string(i + 1) + "\n");
            }
            // Else if */ has been found, set line it is found on as end of comment block
            else if(isWrongCommentBlock && f_contents[i].find("*/") != f_contents[i].npos) {
                node->add_node_text("Wrong comment style ended at line =  " + to_string(i + 1) + "\n");
                errors += "\tWrong comment style ended at line =  " + to_string(i + 1) + "\n";
            }
        }

    }
    node->add_attribute("errors", to_string(error_counter));
    //xml_output +=  " errors = \"" + to_string(error_counter) + "\">\n";
    if(test_ran_successful) {
       // xml_output += "\tNo comment style errors found in file\n";
        test_is_valid = true; // default is false
    }
    else{
        current_xml.base_node->add_child_node(node);
    }
    //xml_output += errors;
    //xml_output += "</" + inspection_name + ">\n";
    //current_xml.add_xml_data(xml_output);
    return test_ran_successful;
}
bool CommentStyle::inspect_and_fix(std::string &file_contents)    {
    //ToDo test has been rewritten and should be tested again!
    //ToDo change stuff to base inspector class, such as xml output and inspection name, also logic etc.
    //ToDo Much of the code is the same as in the inspect, redundant code is bad (fix)!
    std::shared_ptr<XmlNode> node = std::shared_ptr<XmlNode>(new XmlNode("comment-style"));
    //const string inspection_name = "comment-style";
    //string xml_output = "<" + inspection_name;

    string errors;
    string line;
    stringstream sstream1;
    sstream1.str(file_contents);
    vector<string> f_contents;
    bool can_check = true;
    bool isWrongCommentBlock = false;
    bool isWrongDoxygenBlock = false;
    while(std::getline(sstream1, line))
        f_contents.push_back(line);

    bool test_ran_successful = true;

    int starterLine = 0;
    // (\w+\s*[\*\&]*(::)?([=+-><]?){0,2}\s*){1,3}[(](\w*(::)?\w+\s*[\*\&]*\s*\w*(\s*([,]\s*\w*(::)?\w+\s*[\*\&]*\s*\w+)*))?[)]
    int error_counter = 0;
    std::regex test_regex("(\\w+\\s*[\\*\\&]*(::)?([=+-><]?){0,2}\\s*){1,3}[(]((\\w*(::)?)*\\w+\\s*[\\*\\&]*\\s*\\w*(\\s*([,]\\s*(\\w*(::))*?\\w+\\s*[\\*\\&]*\\s*\\w+)*))?[)]");
    std::smatch test_smatch;

    //ToDo Refactor old version
    // New Version:

    // Old Version:
    bool has_been_fixed = false;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        uint32_t pos_next, pos_prev = 0;
        pos_next = f_contents[i].find("\"");
        while(pos_next != f_contents[i].npos)  {
            can_check = !can_check;
            pos_prev = pos_next;
            pos_next = f_contents[i].find("\"", pos_next + 1);
            //can_check = toggle(f_contents[i], 0);
        }
        if(can_check)    {

           /* uint32_t pos;
            int brackets_counter = 0;
            bool is_in_method = false; // start counting brackets
            bool found_method_breaker = false;*/
            uint32_t removeable = 0;

            /*do{
                if(pos = f_contents[i].find("(") != f_contents[i].npos)   { // opening for arguments
                    if(pos = f_contents[i].find(")", pos + 1) != f_contents[i].npos)    { // closing for arguments, if not found search on next line
                        int method_break_counter = 0;
                        while(!found_method_breaker)    {
                            if(f_contents[i + method_break_counter].find(";", pos) != f_contents[i].npos) {// if it cannot find, keep searching on following lines
                                found_method_breaker = true;
                            }
                            else if(f_contents[i + method_break_counter].find("{", pos) != f_contents[i].npos) {
                                is_in_method = true;
                                found_method_breaker = true;
                                brackets_counter++;
                            }
                            ++method_break_counter;
                        }
                        if(f_contents[i].find("{", pos) != f_contents[i].npos) {
                            ++brackets_counter;
                        }
                        else if(f_contents[i].find("}", pos) != f_contents[i].npos) {
                            --brackets_counter;
                            if(brackets_counter == 0)   {
                                is_in_method = false;
                            }
                        }
                    }
                }
            }while(brackets_counter != 0);*/


            if(!has_been_fixed) {
                for(int to_fix = starterLine; to_fix < i; to_fix++)    {
                    //f_contents[i].find("/*");
                    cout << "adding //!" << endl;
                    if(isWrongCommentBlock) {
                        f_contents[to_fix].insert(0, "//");

                    }
                    else if(isWrongDoxygenBlock)    {
                        f_contents[to_fix].insert(0, "//!");

                    }

                }
                isWrongCommentBlock = isWrongDoxygenBlock = false;
                has_been_fixed = true;
            }
/*            if(std::regex_search(f_contents[i].substr(pos_prev), test_smatch, test_regex)) {
                cout << "found method" << endl;
                if(!has_been_fixed) {
                    for(int to_fix = starterLine; to_fix < i; to_fix++)    {
                        //f_contents[i].find("*//*");
                        cout << "adding //!" << endl;
                        f_contents[to_fix].insert(0, "//!");
                    }
                    has_been_fixed = true;
                }
            }*/
            removeable = 0;
            // If wrong doxygen block start has been found
            if((removeable = f_contents[i].find("/**", pos_prev)) != f_contents[i].npos)    {
                f_contents[i].replace(removeable, 3, "");
                starterLine = i;
                //has_been_fixed = false;
                ++error_counter;
                test_ran_successful = false;    // Current inspection ran with failures
                //isWrongCommentBlock = false;     // Wrong comment block detected, set bool to true to also search for endline
                isWrongDoxygenBlock = true;
                node->add_node_text("Wrong doxygen comment style found, started at line = " + to_string(i + 1) + "\n");
            }
/*            else if(isWrongDoxygenBlock && (removeable = f_contents[i].find("*//*", pos_prev)) != f_contents[i].npos) {
                f_contents[i].replace(removeable, 2, "");
            }*/

            else if((removeable = f_contents[i].find("/*", pos_prev)) != f_contents[i].npos)   {
                f_contents[i].replace(removeable, 2, "");
                starterLine = i;
                //has_been_fixed = false;
                ++error_counter;
                test_ran_successful = false;    // Current inspection ran with failures
                isWrongCommentBlock = true;     // Wrong comment block detected, set bool to true to also search for endline
                node->add_node_text("Wrong comment style found, started at line = " + to_string(i + 1) + "\n");
            }
                // Else if */ has been found, set line it is found on as end of comment block
            if(/*(isWrongCommentBlock || isWrongDoxygenBlock) &&*/ (removeable = f_contents[i].find("*/", 0)) != f_contents[i].npos) {
                has_been_fixed = false;
                cout << "AWAITING THE FIX..." << endl;
                f_contents[i].replace(removeable, 2, "");
                node->add_node_text("Wrong comment style ended at line =  " + to_string(i + 1) + "\n");
                errors += "\tWrong comment style ended at line =  " + to_string(i + 1) + "\n";
            }
        }

    }
    string nix;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        nix += f_contents[i];

    }
    file_contents = nix;
    cout << nix << endl;
    node->add_attribute("errors", to_string(error_counter));
    //xml_output +=  " errors = \"" + to_string(error_counter) + "\">\n";
    if(test_ran_successful) {
        // xml_output += "\tNo comment style errors found in file\n";
        test_is_valid = true; // default is false
    }
    else{
        current_xml.base_node->add_child_node(node);
    }
    //xml_output += errors;
    //xml_output += "</" + inspection_name + ">\n";
    //current_xml.add_xml_data(xml_output);
    return test_ran_successful;
}
bool CommentStyle::toggle(string str, uint32_t pos) {
    uint32_t pos_next = str.find("\"", pos);
    if(pos_next != str.npos)  {
        pos_next += 2;
        return !toggle(str, pos_next);
    }
    return false;
}
