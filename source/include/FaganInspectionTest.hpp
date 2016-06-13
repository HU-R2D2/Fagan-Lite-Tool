//! \addtogroup 24 Fagan lite tool
//!
//! \file   DoxygenCheck.hpp
//! \author Ferdi Stoelti
//! \date   06-06-16
//! \brief  Performs the various specified tests on all code files found in the
//! specified folder structure.
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
#ifndef FAGAN_FAGANINSPECTIONTEST_HPP
#define FAGAN_FAGANINSPECTIONTEST_HPP

#include <vector>
#include <string>
//! \brief Contains the main code, that is executed to run the inspections.
class FaganInspectionTest {
public:
    //! \brief By calling the ctor, the main program starts.
    //! \param fileLocations A vector that contains all files that need to be inspected.
    FaganInspectionTest(std::vector<std::string> fileLocations);

private:
    //  Will run all the inspections
    void run_all_inspections(std::vector<std::string> fileLocations);

    //  Retrieves the file contents of the given file location
    std::string get_file_contents(const char *filename);
};


#endif //FAGAN_FAGANINSPECTIONTEST_HPP
