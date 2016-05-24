//! \addtogroup 24 Fagan lite tool
//! \brief <Brief description of module>
//!
//! <Description of module>
//!
//! \file   DoxygenCheck.hpp
//! \author Matthijs Mud 1657223
//! \date   24-05-16
//! \brief  Helps by temporarily treating one buffer as another.
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
#ifndef FAGAN_STREAMREDIRECTOR_HPP
#define FAGAN_STREAMREDIRECTOR_HPP

#include <iostream>

namespace r2d2 {
    class OStreamRedirector final {
    private:
        std::ostream &old_stream;
        std::streambuf * originalBuffer;
    public:
        //! @brief Temporarily use the buffer from the new_stream as that of the
        //! old_stream.
        //!
        //! @param old_stream Stream to have it buffer altered.
        //! @param new_stream Stream with which to share the buffer.
        OStreamRedirector(std::ostream& old_stream, std::ostream& new_stream);
        ~OStreamRedirector();
    };
}

#endif //FAGAN_STREAMREDIRECTOR_HPP
