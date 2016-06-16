//! \addtogroup 24 Fagan lite tool

//! \file   DoxygenCheck.hpp
//! \author Ferdi Stoeltie
//! \date   06-06-16
//! \brief  Utility for helping create an xml file with the found issues.
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
#ifndef FAGAN_XMLFILEFORMAT_HPP
#define FAGAN_XMLFILEFORMAT_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "XmlNode.hpp"
//! @brief Specifies what tag name should be used.
enum class XML_DATA {
    BEGIN,
    END,
    DOXYGEN,
    DEFAULT,
    INCLUSION_GUARD,
    INDENTATION,
};

//! @brief Utility for "easily" creating xml files.
class XmlFileFormat {
public:
    //! @brief Needs to be called, because it sets the default root xml node.
    XmlFileFormat();

    //! @brief Returns all the data contained within XMlFileFormat.
    //! @return std::string Xml data that is contained in XmlFileFormat.
    const std::string data();

    std::shared_ptr<XmlNode> base_node;
private:
    std::vector<std::string> xml_data;
};


#endif //FAGAN_XMLFILEFORMAT_HPP
