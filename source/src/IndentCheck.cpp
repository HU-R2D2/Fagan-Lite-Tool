//
// Created by Matthijs on 6-6-2016.
//

#include "../include/IndentCheck.hpp"
#include <iostream>
#include <regex>
#include <sstream>

namespace r2d2 {
    IndentCheck::IndentCheck(XmlFileFormat &xml) : BaseTest{xml},
                                                   style{"    "} {
    }

    void IndentCheck::set_indent_style(const std::string &style) {
        this->style = style;
    }

    bool IndentCheck::inspect(const std::string &file_contents) {
        // Keeps track of the line number for a clearer error message.
        unsigned int line = 1;
        // Each new scope usually gets a new indent; keep track of it.
        unsigned int scope_level = 0;
        for (auto i = file_contents.begin(); i < file_contents.end(); ++i) {
            char c = *i;
            switch (c) {
                case '\n':
                    ++line;
                    if (!is_indented_correctly(++i, scope_level, i)) {
                        std::stringstream stream{""};
                        stream << "Indentation on line " << line <<
                        " is not according to the standard." << std::endl;
                        current_xml.add_xml_data(XML_DATA::INDENTATION,
                                                 stream.str());
                    }
                    break;
                case '{':
                    //
                    ++scope_level;
                    break;
                case '}':
                    --scope_level;
                    break;
                default:
                    // Keep the compiler happy by supplying all paths.
                    break;
            }
        }
        return false;
    }

    bool IndentCheck::inspect_and_fix(std::string &file_contents) {
        std::string regex_pattern =
                // Marks the beginning of a line/file.
                "(^|\n)"
                        // Maintain any indentation according to the standard.
                        "((" + style + ")*)"
                        //
                        "([ \t]+?)"
                        //
                        "((" + style + ")*\\S)";
        std::regex regex{regex_pattern};
        file_contents = std::regex_replace(file_contents, regex,
                                           "$1$2" + style + "$5");
        return true;
    }

    bool IndentCheck::is_indented_correctly(
            const std::string::const_iterator start_of_line,
            const unsigned int scope_level,
            std::string::const_iterator &end_of_indent) const {

        end_of_indent = start_of_line;
        if (style != "") {
            for (unsigned int i = 0; i < scope_level * style.size(); ++i) {
                char c = *(start_of_line + i);
                switch (c) {
                    // Empty lines are allowed between code lines.
                    // Don't complain about a wrong indent in that case.
                    case '\n':
                    case '\0':
                        return true;
                    case '\r':
                        // Carriage return could be followed by line feed.
                        // Therefore let the decision be based on the next char.
                        break;
                    default:
                        if (c != style[i % style.size()]) {
                            return false;
                        }
                        break;
                }
                end_of_indent = start_of_line + i;
            }
        }
        return true;
    }
}