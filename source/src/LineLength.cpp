//
// Created by fstoeltie on 4/19/16.
//

#include "../include/LineLength.hpp"
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;
LineLength::LineLength(string& f_contents, Test_Type TT) : f_content{f_contents}  , TT{TT}  {
    istringstream iss(f_contents);
    vector<string> strings{istream_iterator<string>{iss},
                          istream_iterator<string>{}};
    for (uint16_t i = 0; i < strings.size() - 1; ++i) {
        if(strings[i].length() > max_line_length)   {
            invalid_line_lengths[i] = strings[i].length();
        }
    }
}
string LineLength::xml_formatted() {
    //ToDo format warnings as correct xml format
    //ToDo Discuss or decide what correct xml format is
    <file file_name = "filename">
        <"invalid line length on lines:">
    </file>
}