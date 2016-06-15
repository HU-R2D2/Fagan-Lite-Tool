//! \addtogroup 24 Fagan lite tool
//! \brief <Brief description of module>
//!
//! <Description of module>
//!
//! \file   DoxygenCheck.hpp
//! \author Ferdi Stoelti
//! \date   6-06-16
//! \brief  Holds the commandline options, while also giving the option to easily
//! extract their value.
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

#ifndef FAGAN_COMMANDLINEOPTIONS_HPP
#define FAGAN_COMMANDLINEOPTIONS_HPP

#include <iostream>
#include <vector>
#include <map>
//! \brief Contains Commands as an enum for easy and readable access.
//!         The values that are linked to the enums,
//!         can be obtained by calling the getCommand method from CommandLineOptions.
//!
enum class Commands : uint16_t {
    INSPECTIONS,
    DIRECTORY,
    CONFIG_FILE,
    OUTPUT_FILE,
};
//! \brief This class contains all of the valid command line options,
//!         that are passed through its ctor as an argument list.
//!
class CommandLineOptions {
public:
    //! \brief The constructor call is required,
    //!         because it validates all the program arguments that are passed in
    //!         by its second argument.
    //!         These cmd line options can then be used by other classes.
    //! \param argc The amount of command arguments that are passed in by its second argument.
    //! \param argv The array, containing all of the arguments that are to be validated and,
    //!             if validated correctly also added as a valid option.
    CommandLineOptions(int argc, char* argv[]);

    //! \brief Contains a link between the Commands and their respective string values,
    //          that are past in as program arguments.
    //!         By passing in a command, a cmd option can be retrieved (if one is available).
    //! @warning WILL BE CHANGED TO PRIVATE, AND METHOD WILL BE AVAILABLE.
    static std::map<Commands, std::string> cmdOptions; // development only
private:

    void checkInspections();    // Check in the cmds argument list,
                                // for arguments that are linked to inspections.

    bool checkDirectory();      //  Check in the cmds argument list,
                                //  for arguments that are linked to the directories.

    bool checkConfigFile();
    std::vector<std::string> cmds;

};


#endif //FAGAN_COMMANDLINEOPTIONS_HPP
