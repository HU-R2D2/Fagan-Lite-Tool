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
    if(test_ran_successful) {
        test_is_valid = true; // default is false
    }
    else{
        current_xml.base_node->add_child_node(node);
    }
    return test_ran_successful;
}
bool CommentStyle::inspect_and_fix(std::string &file_contents)    {
    //ToDo test has been rewritten and should be tested again!
    //ToDo change stuff to base inspector class, such as xml output and inspection name, also logic etc.
    //ToDo Much of the code is the same as in the inspect, redundant code is bad (fix)!
    std::shared_ptr<XmlNode> node = std::shared_ptr<XmlNode>(new XmlNode("comment-style"));

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
    int error_counter = 0;

    //ToDo Refactor old version
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
            uint32_t removeable = 0;
            if(!has_been_fixed) {
                for(int to_fix = starterLine; to_fix < i; to_fix++)    {
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
            if((removeable = f_contents[i].find("*/", 0)) != f_contents[i].npos) {
                has_been_fixed = false;
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
    if(test_ran_successful) {
        test_is_valid = true; // default is false
    }
    else{
        current_xml.base_node->add_child_node(node);
    }
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
