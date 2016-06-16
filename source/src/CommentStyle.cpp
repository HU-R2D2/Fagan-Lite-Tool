#include <sstream>
#include "../include/CommentStyle.hpp"
#include <regex>
CommentStyle::CommentStyle(XmlFileFormat& current_xml)  :
        BaseTest{current_xml} {

}
std::vector<std::string> CommentStyle::f_contents_to_vector(const std::string & file_contents)    {
    std::string line;
    std::stringstream sstream1;
    sstream1.str(file_contents);
    std::vector<std::string> f_contents;
    while(std::getline(sstream1, line))
        f_contents.push_back(line);
    return f_contents;
}
void CommentStyle::replace_comment_type_in_range(int i, int y,  std::vector<std::string>& f_contents)    {
    for(int to_fix = i; to_fix < y; to_fix++)    {
        if(isWrongCommentBlock) {
            f_contents[to_fix].insert(0, "//");
        }
        else if(isWrongDoxygenBlock)    {
            f_contents[to_fix].insert(0, "//!");
        }
    }
    isWrongCommentBlock = isWrongDoxygenBlock = false;
}
bool CommentStyle::inspect(const std::string & file_contents)  {
    //ToDo test has been rewritten and should be tested again!
    //ToDo change stuff to base inspector class,
    //ToDO such as xml output and inspection name, also logic etc.

    std::shared_ptr<XmlNode> node = std::shared_ptr<XmlNode>
            (new XmlNode("comment-style"));

    bool can_check = true;
    //bool isWrongCommentBlock = false;

    std::vector<std::string> f_contents = f_contents_to_vector(file_contents);
    bool test_ran_successful = true;
    int error_counter = 0;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        if(f_contents[i].find("\"") != f_contents[i].npos)  {
            can_check = !can_check;
        }
        if(can_check)    {
            if(f_contents[i].find("/*") != f_contents[i].npos)   {
                ++error_counter;
                test_ran_successful = false;
                isWrongCommentBlock = true;
                node->add_node_text("Wrong comment style found, "
                                            "started at line = " +
                                            std::to_string(i + 1) + "\n");
            }
            else if(isWrongCommentBlock &&
                    f_contents[i].find("*/") != f_contents[i].npos) {
                node->add_node_text("Wrong comment style ended at line =  " +
                                            std::to_string(i + 1) + "\n");
            }
        }
    }
    node->add_attribute("errors", std::to_string(error_counter));
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
    //ToDo change stuff to base inspector class,
    //ToDo such as xml output and inspection name, also logic etc.
    //ToDo Much of the code is the same as in the inspect,
    //ToDo redundant code is bad (fix)!

    bool can_check = true;
/*    bool isWrongCommentBlock = false;
    bool isWrongDoxygenBlock = false;*/

    std::vector<std::string> f_contents = f_contents_to_vector(file_contents);

    //ToDo Refactor old version
    bool has_been_fixed = false;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        uint32_t pos_next, pos_prev = 0;
        pos_next = f_contents[i].find("\"");
        while(pos_next != f_contents[i].npos)  {
            can_check = !can_check;
            pos_prev = pos_next;
            pos_next = f_contents[i].find("\"", pos_next + 1);
        }
        if(can_check)    {
            uint32_t removeable = 0;
            if(!has_been_fixed) {
                replace_comment_type_in_range(starterLine, i, f_contents);
                has_been_fixed = true;
            }
            if((removeable = f_contents[i].find("/**", pos_prev))
                != f_contents[i].npos)    {
                f_contents[i].replace(removeable, 3, "");
                starterLine = i;
                //has_been_fixed = false;
                ++error_counter;
                test_ran_successful = false;
                isWrongDoxygenBlock = true;
                node->add_node_text("Wrong doxygen comment style found, "
                                            "started at line = " +
                                    std::to_string(i + 1) + "\n");
            }
            else if((removeable = f_contents[i].find("/*", pos_prev))
                    != f_contents[i].npos)   {
                f_contents[i].replace(removeable, 2, "");
                starterLine = i;
                ++error_counter;
                test_ran_successful = false;
                isWrongCommentBlock = true;
                node->add_node_text("Wrong comment style found, "
                                            "started at line = " +
                                            std::to_string(i + 1) + "\n");
            }
            if((removeable = f_contents[i].find("*/", pos_prev)) != f_contents[i].npos)
            {
                has_been_fixed = false;
                f_contents[i].replace(removeable, 2, "");
                node->add_node_text("Wrong comment style ended at line =  " +
                                            std::to_string(i + 1) + "\n");
            }
        }
    }
    std::string nix;
    for (uint16_t i = 0; i < f_contents.size(); ++i) {
        nix += f_contents[i];

    }
    file_contents = nix;
    std::cout << nix << std::endl;
    node->add_attribute("errors", std::to_string(error_counter));
    if(test_ran_successful) {
        test_is_valid = true; // default is false
    }
    else{
        current_xml.base_node->add_child_node(node);
    }
    return test_ran_successful;
}
bool CommentStyle::toggle(std::string str, uint32_t pos) {
    uint32_t pos_next = str.find("\"", pos);
    if(pos_next != str.npos)  {
        pos_next += 2;
        return !toggle(str, pos_next);
    }
    return false;
}
