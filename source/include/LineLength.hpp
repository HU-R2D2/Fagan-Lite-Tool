//! \addtogroup 24 Fagan lite tool
//!
//! \file   DoxygenCheck.hpp
//! \author Ferdi Stoelti
//! \date   06-06-16
//! \brief  Makes sure all lines in a file are no longer than the
//! max specified length.
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

#ifndef FAGAN_LINELENGTH_HPP
#define FAGAN_LINELENGTH_HPP

#include <string>
//#include <map>
#include <vector>
#include "Test_Type.hpp"
#include "BaseTest.hpp"

class LineLength : public BaseTest {
public:
    //LineLength(XmlFileFormat& current_xml, std::string& f_contents);


    //! @brief Constructs an object which makes sure all lines are no longer
    //! than the specified max length.
    //!
    //! @param current_xml Utility to write the findings to.
    explicit LineLength(XmlFileFormat &current_xml);

    //! @brief Evaluates whether the length of each line in the specified file
    //! is equal to or less than the specified maximum.
    //!
    //! @param file_contents File to test for lines exceeding max length.
    //! @return Whether all lines in the file abide the maximum amount of
    //! characters per line.
    bool inspect(const std::string &file_contents) override;

    //! @brief Modifies the file in a way all lines are no longer than the
    //! specified maximum amount of characters per line.
    //!
    //! @param file_contents File to modify.
    //! @return Whether or not the file abides the standard.
    //!
    //! @warning As of now no meaningful implementation is given.
    bool inspect_and_fix(std::string &file_contents) { return inspect(file_contents); }

private:
    //std::string& f_content;
    //Test_Type TT;
    const uint8_t max_line_length = 80;
    //std::map< uint16_t, uint16_t  > invalid_line_lengths;
};


#endif //FAGAN_LINELENGTH_HPP
