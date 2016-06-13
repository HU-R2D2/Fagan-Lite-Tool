//! \addtogroup 24 Fagan lite tool
//!
//! \file   CommentStyle.hpp
//! \author Ferdi Stoeltie
//! \date   06-06-16
//! \brief  Makes sure the comment style is conform the specified standard.
//!
//! Currently the standard states that code should be commented using 2
//! consecutive slashes (//), the other way(s(?)) are not allowed. If a slash
//! followed by an asterisk is encountered, this module indicates the file does
//! not match the standard.
//!
//! In future releases, this module should also be able to fix the issues by
//! replacing the occurrences of these comment blocks with either a block of
//! single line comments, or with a preprocessor directive. Though the former
//! is more appalling since comments most likely don't contain compilable code.
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

#ifndef FAGAN_CORRECTCOMMENTSTEST_HPP
#define FAGAN_CORRECTCOMMENTSTEST_HPP


#include "BaseTest.hpp"

class CommentStyle : public BaseTest {
public:
    //! @brief Constructs an object which looks for comments which violate the
    //! coding standard.
    //!
    //! @param current_xml Object to write its findings to.
    explicit CommentStyle(XmlFileFormat &current_xml);

    //! @brief Returns whether the specified file uses comments as specified
    //! in the coding standard.
    //! @param file_contents File to search for invalid comments.
    //! @return Whether or not the file matches the coding standard;
    //! in other words does not contain comment blocks.
    bool inspect(const std::string &file_contents) override;

    //! @brief Replaces all instances of invalid comment styles with a valid one.
    //!
    //! @param file_contents File to rid of invalid comments.
    //! @return Whether or not the file matches the coding standard;
    //! in other words does not contain comment blocks.
    //!
    //! @warning No meaningful implementation is given as of now.
    bool inspect_and_fix(std::string &file_contents) {
        return inspect(file_contents);
    }

private:
};


#endif //FAGAN_CORRECTCOMMENTSTEST_HPP
