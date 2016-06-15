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

#ifndef FAGAN_HEADERCHECK_HPP
#define FAGAN_HEADERCHECK_HPP

#include "BaseTest.hpp"
#include "DoxygenTool.hpp"

namespace r2d2 {
    class HeaderCheck : public BaseTest {
    private:
        std::string default_header;
        std::string current_file;
        DoxygenTool tool;

        //! @brief Gets the current date as a string in the format DD-MM-YYYY.
        //! @return
        std::string now_date() const;
        
    public:
        //! @brief Constructs a utility to test whether a file contains a
        //! specific header.
        //!
        //! @param xml Target file to write found errors to.
        explicit HeaderCheck(XmlFileFormat & xml);

        //! @brief Sets the default header to test for by reading it from the
        //! specified file.
        //!
        //! @param path Name of the file containing the default header.
        void open_header(const std::string & path);

        //! @brief Specifies the filename to insert when fixing a missing or
        //! incomplete header.
        //!
        //! It should be noted that if this method is not performed,
        //!
        //! @param file_name Name of the file to insert.
        void set_current_file(const std::string & file_name);

        //! @brief Makes sure the header is present.
        //!
        //! @param String representing the contents of the file.
        //! @return Whether the file contains the specified header.
        bool inspect(const std::string & file_contents) override;

        //! @brief Inserts a header and fills all fields it knows.
        //!
        //! It is advised to specify the name of the file which is being
        //! inspected using the method "set_current_file" before fixing said
        //! file. Incorrect file tags are inserted in the file otherwise.
        //!
        //! @param String representing the contents of the file.
        //! Changes are made on it in order to fix it.
        //! @return Whether the file contains the specified header.
        bool inspect_and_fix(std::string & file_contents) override;
    };
}

#endif //FAGAN_HEADERCHECK_HPP
