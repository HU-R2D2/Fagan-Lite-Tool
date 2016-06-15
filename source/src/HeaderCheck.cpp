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
    std::string HeaderCheck::now_date() const{
        //http://stackoverflow.com/questions/16357999/current-date-and-time-as-string
        time_t rawtime;
        struct tm * timeinfo;
        // DD-MM-YYYY, with a slight margin.
        char buffer[16];
        time (&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
        return std::string(buffer);
    }

    bool HeaderCheck::inspect(const std::string &file_contents) {

        auto node = std::shared_ptr<XmlNode>(new XmlNode{"header"});

        // Match the last line of the header to figure out whether a header is
        // present. This however assumes the author did not include a line
        // in the same format (quite unlikely someone would).
        std::regex regex{
                "<\\s* HEADER_VERSION "
                        "(\\d\\d\\d\\d)\\s*"    // Capture year.
                        "-?\\s*(\\d\\d)\\s*"    // Capture month.
                        "-?\\s*(\\d\\d)\\s*>"}; // Capture day.
        std::smatch match_file{};
        std::smatch match_header{};
        // Both the templated header and that of the file should include the
        // line, as a newer version missing this possibly ivalidates this step.
        if (std::regex_search(file_contents, match_file, regex) &&
            std::regex_search(default_header, match_header, regex)) {
            // Make sure the entire date matches.
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

        // This
        node->add_node_text("No header was found.");
        current_xml.base_node->add_child_node(node);
        return false;
    }

    bool HeaderCheck::inspect_and_fix(std::string &file_contents) {
        // Only insert the "correct" version of the header when the one present
        // (if any), is not the most up to date version.
        if (!inspect(file_contents)) {
            std::stringstream stream{""};

            // Get some known fields which typically are always present in
            // a header. This way the author does not need to assign them.

            // The object calling this function should first set the value
            // by calling set_current_file.
            stream << "//! \\file \"" << current_file << "\"" << std::endl;
            for (const auto & author : tool.get_authors(file_contents)) {
                stream << "//! \\author " << author << std::endl;
            }
            // Insert the found version, which could mean nothing.
            // If it is missing in the existing file insert nothing,
            // as there is no way to give it a meaningful version otherwise.
            const auto version = tool.get_version(file_contents);
            if (version.size()) {
                stream << "//! \\version " << tool.get_version(file_contents) <<
                std::endl;
            }

            // If a date was specified in the file use it. Otherwise use the
            // current date as someone probably won't update fossilized code
            // missing a date using this tool.
            const auto date = tool.get_date(file_contents);
            stream << "//! \\date " << (date.size() ? date : now_date()) << std::endl;

            file_contents.insert(0, (stream.str() + default_header));
        }
        return true;


    }

    HeaderCheck::HeaderCheck(XmlFileFormat &xml) : BaseTest{xml} {

    }

    void HeaderCheck::set_current_file(const std::string &file_name) {
        current_file = file_name;

    }

    void HeaderCheck::open_header(const std::string &path) {
        // Open the file at the end of the file to determine its size.
        std::fstream file{path, std::ios_base::in | std::ios_base::ate};
        if (file.is_open()) {
            // Reserve space to avoid unnecessary memory allocations.
            default_header.reserve(static_cast<unsigned int>(file.tellg()));

            // Keep the contents of the file in memory to assign them later.
            file.seekg(0, std::ios_base::beg);
            default_header.assign(std::istreambuf_iterator<char>(file),
                                  std::istreambuf_iterator<char>());
            file.close();
        } else {
            throw std::invalid_argument{"File at path could not be opened."};
        }

    }
}
