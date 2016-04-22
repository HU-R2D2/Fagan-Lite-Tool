////
// \project Roborescue
// \package r2d2
//
// \file DoxygenTool.cpp
// \date Created: 08-04-16
// \version 1.0
//
// \author Matthijs Mud
//
// \section LICENSE
// License: newBSD
//
// Copyright © 2016, HU University of Applied Sciences Utrecht.
// All rights reserved.
//
// Redistribution and use in source and binary forms,
// with or without modification, are permitted provided that
// the following conditions are met:
// - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// - Neither the name of the HU University of Applied Sciences Utrecht
//   nor the names of its contributors may be used to endorse or promote
//   products derived from this software without specific prior written
//   permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////

#include "../include/DoxygenTool.hpp"
#include <iostream>
#include <regex>

namespace r2d2 {

    r2d2::DoxygenTool::DoxygenTool() {

    }

    const std::string DoxygenTool::get_author(const std::string &file) const {
        return get_annotated(strip_comment(file), "author")[0];
    }

    const std::string DoxygenTool::get_date(const std::string &file) const {
        return get_annotated(strip_comment(file), "date")[0];
    }

    const std::string DoxygenTool::get_version(const std::string &file) const {
        return get_annotated(strip_comment(file), "version")[0];
    }

    const std::vector<std::string> DoxygenTool::get_annotated(
            const std::string &section,
            const std::string &annotation) const {
        std::vector<std::string> annotated_values{};
        std::string::const_iterator begin = section.begin();
        const std::string::const_iterator end = section.end();
        // Since a backslash and at-sign could indicate the start of an
        // annotation, "[\\\\@]" is used. If a backslash should be matched in
        // a regex, it should be preceded by a backslash. The same applies for
        // the compiler; hence the quadruple backslash. "\\s" is used to match a
        // whitespace character.
        const std::string annotated_value_regex
                = "([\\\\@]" + annotation + "\\s)"
                  // Match any number of "words" until the next paragraph.
                  // Though try to match the minimum amount possible to still
                  // create a complete match.
                  + "([\\s\\S]*?)"
                  // The end of an annotation is either indicated by:
                  // - The end of a paragraph;
                  //   which is specified as 2 or more consecutive line breaks
                  //   ("(\r?\n[\t ]*){2,}"), ignoring trailing whitespace.
                  // - The end of the string "$".
                  // - Or the start of a different annotation ("\\s@\\S+").
                  + "(?=((\r?\n[\t ]*){2,}|$|(\\s*[\\\\@]\\S+)))";

        std::regex regex{annotated_value_regex};
        std::smatch match{};
        while (std::regex_search(begin, end, match, regex)) {
            annotated_values.push_back(match[2].str());
            begin = match.suffix().first;
        }
        return annotated_values;
    }

    const std::vector<std::string> DoxygenTool::get_blocks(
            const std::string &file) const {
        std::string::const_iterator begin = file.begin();
        const std::string::const_iterator end = file.end();

        std::vector<std::string> comment_blocks{};
        try {
            std::regex regex{
                    "" // Continue on next line.
                            // Match a block of multiple single line comments.
                            // By starting with "[\t ]*", indented lines can
                            // also be matched.
                            // "[\\S\t ]*" is used to find printable characters
                            // and single line whitespace.
                            // A non-comment line specifies the end of a block.
                            // This could either be an empty line, or 'runnable'
                            // code.
                            "(([\t ]*//(!|/)[\\S\t ]*((\r?\n)|\\0))+)"

                            "|" // Supply an alternative way to define blocks.

                            // Match a comment block which is specified as /* */
                            // Any number of characters is allowed between the
                            // opening and closing sequence.
                            "(/\\*\\*[\\s\\S]*?\\*/)"
            };
            std::smatch match{};
            // A file could match the search pattern multiple times.
            // Keep trying to find matches until no more matches are found.
            while (std::regex_search(begin, end, match, regex)) {
                comment_blocks.push_back(match.str());

                // Ignore the part which was just scanned.
                // The loop would otherwise not end, as the same match is found.
                begin = match.suffix().first;
            }

        } catch (std::regex_error &e) {
            //
            std::cerr << "Error: " << e.what() << std::endl;
            exit(2);
        }
        return comment_blocks;
    }

    const std::vector<std::string> DoxygenTool::get_authors(
            const std::string &file) const {
        return get_annotated(strip_comment(file), "author");
    }

    const std::string DoxygenTool::strip_comment(
            const std::string &section) const {
        std::regex regex{"(([\\t ]*//(!|/))|([\t ]*\\*))[\t ]?"};
        return std::regex_replace(section, regex, "");
    }
}