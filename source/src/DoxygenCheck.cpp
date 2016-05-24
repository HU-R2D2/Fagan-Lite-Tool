//! \addtogroup 24 Fagan lite tool
//! \brief <Brief description of module>
//!
//! <Description of module>
//!
//! \file   DoxygenCheck.hpp
//! \author Matthijs Mud 1657223
//! \date   22-04-16
//! \date   22-04-16
//! \brief  Performs various checks on the doxygen comments in any specified file.
//!
//! The various checks include:
//! - whether or not each comment block contains a brief description;
//! - The file includes the copyright notice, and whether all fields are
//!   replaced so the standard values no longer remain. (checking for the actual
//!   author is practically impossible.)
//! -
//!
//! \copyright Copyright © 2016, HU University of Applied Sciences Utrecht.
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

#include "../include/DoxygenTool.hpp"
#include "../include/DoxygenCheck.hpp"
#include "../include/StreamRedirector.hpp"
#include <sstream>
#include <algorithm>
#include <regex>

namespace r2d2 {
    DoxygenCheck::DoxygenCheck(XmlFileFormat &xml)
            : BaseTest{xml}, tool{} {

    }

    bool DoxygenCheck::check_author(const std::string &file) const {
        bool result = true;
        int number_of_authors = 0;
        for (const std::string &comment : tool.get_blocks(file)) {
            const std::vector<std::string> authors = tool.get_authors(comment);
            number_of_authors += authors.size();
            result = result && test_invalid_tag("author", authors, file);
        }
        if (!number_of_authors) {
            std::cerr << "No authors are specified in the file." << std::endl;
        }
        return result && number_of_authors;
    }

    bool DoxygenCheck::check_brief(const std::string &file) const {
        // Test whether each doxygen comment block has a brief description.
        bool result = true;

        for (const std::string &comment : tool.get_blocks(file)) {
            if (!tool.get_annotated(comment, "brief").size()) {
                auto comment_line = get_line_number(comment, file);
                auto comment_size = std::count(comment.begin(), comment.end(),
                                               '\n') - 1;

                std::cerr << "Doxygen comment on line(s) " <<
                comment_line << " through " << (comment_line + comment_size) <<
                " does not contain a brief description." << std::endl;
                result = false;
            }
        }
        return result;
    }

    bool DoxygenCheck::check_version(const std::string &file) const {
        std::vector<std::string> versions{};
        for (const std::string &comment : tool.get_blocks(file)) {
            const std::string version = tool.get_version(comment);
            if (version != "") {
                versions.push_back(version);
            }
        }
        if (versions.size() != 1) {
            std::cerr <<
            "A file should have 1 version specified; no more no less." <<
            std::endl;
            for (auto const &i : versions) {
                std::cerr << "Version on line: " << get_line_number(i, file) <<
                std::endl;
            }
            return false;
        }
        return true;
    }

    size_t DoxygenCheck::get_line_number(const std::string &text,
                                         const std::string &file) const {
        const auto index = file.find(text);
        // Line count starts at 1 by default.
        return ((file.begin() + index) != file.end())
               ? static_cast<size_t>(1 + std::count(file.begin(), file.begin() +
                                                                  file.find(
                                                                          text),
                                                    '\n'))
               : static_cast<size_t>(-1);
    }

    void DoxygenCheck::add_invalid_tag_value(const std::string &tagname,
                                             const std::string &value) {
        invalid_tag_values[tagname].push_back(value);
    }

    bool DoxygenCheck::test_invalid_tag(const std::string &tagname,
                                        const std::vector<std::string> &values,
                                        const std::string &file) const {
        bool result = true;
        for (const std::string &value : values) {
            if (invalid_tag_values.find("value") !=
                invalid_tag_values.end()) {
                for (const auto &invalid_tag :invalid_tag_values.at(
                        "value")) {
                    if (value == invalid_tag) {
                        std::cerr << tagname << " on line " <<
                        get_line_number(value, file) << " is specified as \"" <<
                        value << "\" which is not allowed." << std::endl;
                        result = false;
                    }
                }
            }
        }
        return result;
    }

    bool DoxygenCheck::inspect(const std::string &file_contents) {
        std::function<bool(DoxygenCheck *, const std::string &)> checks[] = {
                //bool (*checks[])(r2d2::DoxygenCheck *, const std::string &) const ={
                &check_author,
                &check_brief,
                &check_version,
        };
        bool result = true;
        for (auto &check : checks) {
            std::stringstream output;
            // Used to restore the default error stream in case of exceptions.
            OStreamRedirector osr{std::cerr, output};
            if (!check(this, file_contents)) {
                current_xml.add_xml_data(XML_DATA::DOXYGEN, output.str());
                result = false;
            }
        }

        return result;
    }

    bool DoxygenCheck::inspect_and_fix(std::string &file_contents) {
        //
        return inspect(file_contents);
    }
}