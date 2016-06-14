//! \addtogroup 24 Fagan lite tool
//! \brief <Brief description of module>
//!
//! <Description of module>
//!
//! \file   DoxygenCheck.hpp
//! \author Matthijs Mud 1657223
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

#include "../include/HeaderCheck.hpp"
#include <fstream>
#include <regex>

namespace r2d2 {
    bool HeaderCheck::inspect(const std::string &file_contents) {

        auto node = std::shared_ptr<XmlNode>(new XmlNode{"header"});

        std::regex regex{
                "<\\s* HEADER_VERSION "
                        "(\\d\\d\\d\\d)\\s*" // Capture year.
                        "(\\d\\d)\\s*"       // Capture month.
                        "(\\d\\d)\\s*>"};   // Capture day.
        std::smatch match_file{};
        std::smatch match_header{};
        if (std::regex_search(file_contents, match_file, regex) &&
            std::regex_search(default_header, match_header, regex)) {
            if ((match_file[1] == match_header[1]) &&
                (match_file[2] == match_header[2]) &&
                (match_file[3] == match_header[3])) {
                return true;
            } else {
                node->add_node_text("Version of the header is incorrect.");
                current_xml.base_node->add_child_node(node);
                return false;
            }
        }

        node->add_node_text("No header was found.");
        current_xml.base_node->add_child_node(node);
        return false;
    }

    bool HeaderCheck::inspect_and_fix(std::string &file_contents) {
        //TODO: Fix the issue with the header.
        if (!inspect(file_contents)) {
            std::stringstream stream{""};

            stream << "//! \\file \"" << current_file << "\"" << std::endl;
            for (const auto & author : tool.get_authors(file_contents)) {
                stream << "//! \\author " << author << std::endl;
            }
            stream << "//! \\version " << tool.get_version(file_contents) << std::endl;
            stream << "//! \\date " << tool.get_date(file_contents) << std::endl;
            file_contents.insert(0, (stream.str() + default_header));
        }
        return inspect(file_contents);


    }

    HeaderCheck::HeaderCheck(XmlFileFormat &xml) : BaseTest{xml} {

    }

    void HeaderCheck::set_current_file(const std::string &file_name) {
        current_file = file_name;

    }

    void HeaderCheck::open_header(const std::string &path) {
        std::fstream file{path, std::ios_base::in | std::ios_base::ate};
        if (file.is_open()) {
            default_header.reserve(static_cast<unsigned int>(file.tellg()));
            file.seekg(0, std::ios_base::beg);

            default_header.assign(std::istreambuf_iterator<char>(file),
                                  std::istreambuf_iterator<char>());
            file.close();
        } else {
            throw std::invalid_argument{"File at path could not be opened."};
        }

    }
}