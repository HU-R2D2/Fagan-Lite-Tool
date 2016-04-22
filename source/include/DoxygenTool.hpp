////
// \project Roborescue
// \package r2d2
//
// \file DoxygenTool.hpp
// \date Created: 08-04-16
// \version <0.0.0>
//
// \author Matthijs Mud 1657223
//
// \section LICENSE
// License: newBSD
//
// Copyright © 2016, HU University of Applied Sciences Utrecht.
// All rights reserved.
//
// Redistribution and use in source and binary forms,
// with or without modification, are permitted provided that
// the following conditions are met:
// - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// - Neither the name of the HU University of Applied Sciences Utrecht
//   nor the names of its contributors may be used to endorse or promote
//   products derived from this software without specific prior written
//   permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////
#ifndef HEADERTOOL_HPP
#define HEADERTOOL_HPP

#include <iostream>
#include <vector>

namespace r2d2 {
    //! @brief Class which helps extracting elements from doxygen comments.
    //!
    //! @warning
    //! Some versions of certain compilers might not give an implementation for
    //! Regular Expressions (regex for short), despite giving the declaration.
    //! As this module makes usage of said namespace, make sure it is implemented.
    class DoxygenTool final {
    private:
        DoxygenTool(const DoxygenTool& rhs) = delete;
        DoxygenTool &operator=(const DoxygenTool& rhs) = delete;
    public:
        const std::vector<std::string> get_authors(const std::string & file) const;

        //! @brief
        //!
        //!
        const std::string get_author(const std::string &file) const;

        const std::string get_date(const std::string &section) const;

        const std::string get_version(const std::string &section) const;

        //! @brief Removes comment specific characters from a string.
        //!
        //! Removed characters include leading whitespace, asterisks, and
        //! multiple slashes. A single, directly trailing, whitespace to the
        //! decoration is also removed. Therefore the structure is maintained.
        //!
        //! @param section Comment string to remove characters from.
        //! @return String stripped from characters which won't appear in Doxygen.
        const std::string strip_comment(const std::string & section) const;

        //! @brief Gets all the follow-up for specified annotation in the section.
        //!
        //! @param section Piece of code to look for the annotation.
        //! @param annotation
        //! @return Gets a collection of thingies
        const std::vector<std::string> get_annotated(const std::string &section,
                                        const std::string &annotation) const;

        //! @brief Gets all doxygen comment blocks in the file.
        //!
        //! Returns blocks of comments which are specified in one of doxygen's
        //! formats. This could either be 3 slashes (///), 2 slashes and an
        //! exclamation mark (//!) or 1 slash 2 asterisks ending in an asterisk
        //! and slash (/** */). Aside from the last block, all blocks
        //! should be specified on consecutive lines, with a similar style.
        //! This means an empty line, a line of code or another comment style,
        //! ends the block; thus starting a new block.
        //!
        //! @param file Contents of the file to extract blocks from.
        //! @return A list containing all found blocks.
        const std::vector<std::string> get_blocks(const std::string& file) const;
        DoxygenTool();
    };
}

#endif //HEADERTEST_HPP
