//! \addtogroup 24 Fagan lite tool
//!
//! \file   DoxygenCheck.hpp
//! \author Ferdi Stoelti
//! \date   06-06-16
//! \brief  Supplies an interface for a generic test to perform on each file.
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

#ifndef FAGAN_BASETEST_HPP
#define FAGAN_BASETEST_HPP

#include "XmlFileFormat.hpp"

// @author Ferdi Stoeltie
// @date 11-05-16
// @brief This is the base class for all tests. It provides two methods
// (inspect and inspect_and_fix). These methods can be used to run the fagan
// test and only inspect or inspect and fix where possible. Other than these two
// methods, it contains a reference to a XmlFileFormat object to write its
// results to.
// @warning This class is only meant to be inherited from!
class BaseTest {
public:
    //! @brief Constructor taking in a XmlFileFormat and storing the reference.
    //! @param current_xml A reference to a XmlFileFormat object. It will write
    //! its test results to this.
    explicit BaseTest(XmlFileFormat &current_xml) : current_xml{current_xml} { }

    //! @brief Virtual method that will be overwritten to contain the fagan
    //! inspection tests.
    //!
    //! @param file_contents contents of the file to inspect.
    //! @return True indicates found deviations from standard do not exist.
    //! @warning Pure method!
    virtual bool inspect(const std::string &file_contents) = 0;

    //! @brief Virtual method that will be overwritten to contain the fagan
    //! inspection tests,
    //! and fix the issues wherever possible.
    //!
    //! @param file_contents Contents of the file to inspect and possibly change.
    //! @return True indicates found deviations from standard do not exist
    //! after performing possible fixes.
    //! @warning Pure method!
    virtual bool inspect_and_fix(std::string &file_contents) = 0;

    //! @brief Returns the boolean that contains the result that is stored by
    //! running inspect OR inspect_and_fix.
    //!
    //! Should only be checked after running inspect OR inspect_and_fix,
    //! otherwise it is always false.
    //! @return Returns true if the test has run successful and false otherwise.
    //! @warning Only use after running one of the fagan inspection test methods
    //! (inspect, inspect_and_fix).
    const bool is_valid() { return test_is_valid; }

protected:
    XmlFileFormat &current_xml; // Reference to the XMlFileFormat object, to write to.
    bool test_is_valid = false; // Boolean containing test resulsts.
};


#endif //FAGAN_BASETEST_HPP
