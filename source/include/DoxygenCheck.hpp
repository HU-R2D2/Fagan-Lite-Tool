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

#ifndef FAGAN_DOXYGENCHECK_HPP
#define FAGAN_DOXYGENCHECK_HPP

#include "DoxygenTool.hpp"
#include "BaseTest.hpp"
#include <vector>
#include <map>

namespace r2d2 {
    class DoxygenCheck final : public BaseTest {
    private:
        DoxygenTool tool;
        std::map<std::string, std::vector<std::string>> invalid_tag_values;

        size_t get_line_number(const std::string &text,
                               const std::string &file) const;

        bool test_invalid_tag(const std::string &tagname,
                              const std::vector<std::string> &values,
                              const std::string &file) const;

    public:
        //! @brief Checks whether an author is specified other than the default.
        //!
        //! Per comment block lacking a "brief" tag a description is written
        //! to the std::cerr.
        //!
        //! @return Whether all specified authors were valid.
        bool check_version(const std::string &file) const;

        //! @brief Checks whether an author is specified other than the default.
        //!
        //! Per comment block lacking a "brief" tag a description is written
        //! to the std::cerr.
        //!
        //! @return Whether all specified authors were valid.
        bool check_author(const std::string &file) const;

        //! @brief Tests whether each comment block in the file contains a
        //! "brief" tag.
        //!
        //! Per comment block lacking a "brief" tag a description is written
        //! to the std::cerr.
        //!
        //! @param file
        //! @return Whether all comment blocks contain a brief description
        //! (true), or not (false).
        bool check_brief(const std::string &file) const;

        //! @brief
        //!
        void add_invalid_tag_value(const std::string &tagname,
                                   const std::string &value);

        bool inspect(const std::string & file_contents) override;

        bool inspect_and_fix(std::string & file_contents) override;

        explicit DoxygenCheck(XmlFileFormat & xml);
    };
}


#endif //FAGAN_DOXYGENCHECK_HPP
