//
// Created by Matthijs on 6-6-2016.
//

#include "../include/IndentCheck.hpp"
#include <regex>

namespace r2d2 {
    IndentCheck::IndentCheck(XmlFileFormat &xml) : BaseTest{xml} {
    }
    void IndentCheck::set_indent_style(const std::string & style) {
        this->style = style;
    }

    bool IndentCheck::inspect(const std::string &file_contents) {
        return false;
    }

    bool IndentCheck::inspect_and_fix(std::string &file_contents) {
        std::string regex_pattern = "(" + style + ")*(\\s)*";
        std::regex regex{};
        std::smatch match;
        //std::regex_replace(file_contents, regex);
        return true;
    }
}