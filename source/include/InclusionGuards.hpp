//! \addtogroup 24 Fagan lite tool
//!
//! \file   DoxygenCheck.hpp
//! \author Ferdi Stoelti
//! \date   06-06-16
//! \brief  Tests for a given header file whether an inclusion guard is
//! specified in the form of ifndef, define, endif.
//!
//! While it is possible to perform the test on files other than headers,
//! but this is practically useless as these files typically don't include
//! inclusion guards; which would result in all tests failing.
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
#ifndef FAGAN_INCLUSIONGUARDS_HPP
#define FAGAN_INCLUSIONGUARDS_HPP

#include "BaseTest.hpp"

class InclusionGuards : public BaseTest {
public:
    //! @brief Constructs an object which checks whether a file includes an
    //! inclusion guard.
    //!
    //! @param current_xml Utility to write the findings to.
    explicit InclusionGuards(XmlFileFormat &current_xml);

    //! @brief whether a file includes an inclusion guard.
    //!
    //! @param file_contents Content of the file to check.
    //! @return Whether an inclusion guard is available, and according to the
    //! standard.
    bool inspect(const std::string &file_contents) override;

    //! @brief Inserts an inclusion guard if it is missing.
    //! @param file_contents File to modify.
    //! @return Whether a inclusion guard is present according to the standard.
    //!
    //! @warning Currently not implemented in a meaningful way.
    bool inspect_and_fix(std::string &file_contents) { return false; }

private:
};


#endif //FAGAN_INCLUSIONGUARDS_HPP
