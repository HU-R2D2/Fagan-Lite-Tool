//! \addtogroup 24 Fagan lite tool
//!
//! \file   IndentCheck.hpp
//! \author Matthijs Mud 1657223
//! \date   08-06-16
//! \brief  Tests whether the indentation in any given file is according to
//! the specified standard.
//!
//!
//!
//! \copyright Copyright � 2016, HU University of Applied Sciences Utrecht.
//! All rights reserved.
//!
//! License: newBSD
//!
//! Redistribution and use in source and binary forms,
//! with or without modification, are permitted provided that
//! the following conditions are met:
//! - Redistributions of source code must retain the above copyright notice,
//!   this list of conditions and the following disclaimer.
//! - Redistributions in binary form must reproduce the above copyright notice,
//!   this list of conditions and the following disclaimer in the documentation
//!   and/or other materials provided with the distribution.
//! - Neither the name of the HU University of Applied Sciences Utrecht
//!   nor the names of its contributors may be used to endorse or promote
//!   products derived from this software without specific prior written
//!   permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//! "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
//! BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
//! AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//! IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
//! BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//! OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//! WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//! OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//! EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ~< HEADER_VERSION 2016 04 12 >~

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

        unsigned  int errors = 0;
        // Each new scope usually gets a new indent; keep track of it.
        auto node = std::shared_ptr<XmlNode>(new XmlNode("Indentation"));
        current_xml.base_node->add_child_node(node);

        unsigned int scope_level = 0;
        for (auto i = file_contents.begin(); i < file_contents.end(); ++i) {
            char c = *i;
            switch (c) {
                case '\n':
                    ++line;
                    if (!is_indented_correctly(i, scope_level, i)) {
                        std::stringstream stream{""};
                        stream << "Indentation on line " << line <<
                        " is not according to the standard."
                        << " Encountered unexpected character \'"
                        << (*(i+1)) << "\'" << std::endl;
                        node->add_node_text(stream.str());
                        ++errors;
                    }
                    break;
                case '{': // }
                    //
                    ++scope_level;
                    break;
                case '}': // {
                    --scope_level;
                    break;
                default:
                    // Keep the compiler happy by supplying all paths.
                    break;
            }
        }
        node->add_attribute("errors", std::to_string(errors));
        return false;
    }

    bool IndentCheck::inspect_and_fix(std::string &file_contents) {
#ifdef DONT_COMPILE
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
#endif // DONT_COMPILE
        return inspect(file_contents);
    }

    bool IndentCheck::is_indented_correctly(
            const std::string::const_iterator start_of_line,
            const unsigned int scope_level,
            std::string::const_iterator &end_of_indent) const {

        end_of_indent = start_of_line;
        if (style != "") {
            for (unsigned int i = 0; i < scope_level * style.size(); ++i) {
                char c = *(start_of_line + i + 1);
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
                    case '}':
                        if (i == ((scope_level - 1) * style.size())) {
                            return true;
                        }
                        break;
                    default:
                        if (c != style[i % style.size()]) {
                            return false;
                        }
                        break;
                }
                end_of_indent = start_of_line + i + 1;
            }
        }
        return true;
    }
}