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
#ifndef FAGAN_INDENTCHECK_HPP
#define FAGAN_INDENTCHECK_HPP

#include "BaseTest.hpp"

namespace r2d2 {
    class IndentCheck : public BaseTest {
    private:
        // Style used for indent. By default this is set to 4 spaces.
        std::string style;

        //! @brief Checks if the the text starting at the given point includes
        //! as many indents as the scope level warrants.
        //!
        //! Starting at the given point in the string, this function tests
        //! whether the pattern is repeated at least as often as the scope_level.
        //! Besides a complete match of the pattern, the following cases also
        //! result in a line indented according to the standard:
        //! - The number of found indents is exactly one less than specified
        //! and he very next character is a closing bracket. This indicates the
        //! end of the scope.
        //! - A line break is encountered. While unusual halfway a line,
        //! some IDEs have the tendency to strip whitespace at the end of a
        //! blank line. In this case the indent would not match.
        //!
        //! @param start_of_line Point representing start of line.
        //! @param scope_level How often the indent should be repeated.
        //! @param end_of_indent Points to the last character considered part of
        //! the indentation (if any), otherwise it matches start of line.
        //! @return Whether the specified line is indented correctly.
        bool is_indented_correctly(
                const std::string::const_iterator start_of_line,
                const unsigned int scope_level,
                std::string::const_iterator &end_of_indent) const;

    public:
        IndentCheck(XmlFileFormat &xml);

        //! @brief Sets the pattern representing 1 indentation.
        //!
        //! Patterns you would typically specify include only spaces and tabs.
        //! Characters like brackets and line breaks are handled in a special
        //! way, as such they should be avoided.
        //!
        //! @param style The pattern to set.
        void set_indent_style(const std::string &style);

        //! @brief Tests whether the specified file is indented according to
        //! the supplied standard.
        //!
        //! @param file_contents Contents of file to check for indent abuse.
        //! @return Whether or not all lines match the indentation standard.
        //!
        //! @warning Raw strings spanning multiple lines will end up in
        //! exceptions unless they include an unusual amount of indents.
        //! @warning Some IDEs move pre-compile directives to the start of the
        //! line. In this case that line will end up being indented against the
        //! standard. The same apply for access keywords (private, public, etc.)
        //! @warning This utility does not (yet) check for context. As such it
        //! expects more/less indents when it encounters a bracket ({}) in a
        //! string or comment, where it does not warrant a new scope or exit
        //! thereof.
        bool inspect(const std::string &file_contents) override;

        //! @brief Fixes the indentation in the given file to match the standard.
        //!
        //! @param Contents of file which will be adjusted.
        //! @return True, as the standard is forced.
        //!
        //! @warning Not implemented yet.
        //! @warning Raw strings spanning multiple lines might end up getting
        //! multiple indents where they aren't supposed to be.
        bool inspect_and_fix(std::string &file_contents) override;
    };
}

#endif //FAGAN_INDENTCHECK_HPP
