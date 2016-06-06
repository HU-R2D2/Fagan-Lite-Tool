////
// \project Roborescue
// \package r2d2
//
// \file DoxygenTool.cpp
// \date Created: 08-04-16
// \version 1.0
//
// \author Matthijs Mud
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

#include <sstream>
#include "gtest/gtest.h"
#include "../source/include/DoxygenTool.hpp"
#include "../source/include/DoxygenCheck.hpp"
#include "../source/include/StreamRedirector.hpp"

#define SHOW_RESULTS
using namespace r2d2;

TEST(DoxygenTool, commentBlocks) {
    const auto &comment_block1 = ""
            "//! Commentblock 1\n"
            "//! @brief\n"
            "//! @param argc Number of commandline parameters.\n"
            "//! @param argv The actual parameters.\n";

    const auto &comment_block2 = ""
            "/**\n"
            " * @brief Something something.\n"
            " *\n"
            " * A somewhat more indepth description.\n"
            " */";

    std::string test_case{};
    test_case += comment_block1;
    test_case += "\n";
    test_case += comment_block2;
    DoxygenTool tool;
    std::vector<std::string> comments = tool.get_blocks(test_case);

    EXPECT_EQ(comment_block1, comments[0]) << "";
    EXPECT_EQ(comment_block2, comments[1]) << "";

#ifdef SHOW_RESULTS
    for (const auto & comment : comments) {
        std::cout << "Comment: " << std::endl << comment << std::endl;
    }
#endif
}

TEST(DoxygenTool, author) {
    const auto &test = ""
            "//! @author Alpha Bravo\n"
            "//! \\author\n"
            "//! Charlie Delta\n"
            "//! @brief Some irrelevant code.\n"
            "//! \\author Echo Foxtrot\n"
            "//! \n"
            "//! Descriptive text which should not be part of an author.\n"
            "//! @author Golf Hotel";
    DoxygenTool tool;

    const std::vector<std::string> authors = tool.get_authors(test);
    ASSERT_GE(4u, authors.size()) << "At least 2 authors should be found";
    EXPECT_EQ("Alpha Bravo", authors[0]) << "First author was incorrect";
    EXPECT_EQ("Charlie Delta", authors[1]) << "Second author was incorrect";
    EXPECT_EQ("Echo Foxtrot", authors[2]) << "Third author was incorrect";
    EXPECT_EQ("Golf Hotel", authors[3]) << "Fourth author was incorrect";
    EXPECT_EQ(4u, authors.size()) << "More authors were found than expected.";
#ifdef SHOW_RESULTS
    for (const auto & author : authors) {
        std::cout << "Author: " << std::endl << author << std::endl;
    }
#endif
}

TEST(DoxygenCheck, all) {

    // Make sure that when an exception occurs, the streams are returned to how
    // they originally were. It could otherwise give strange results.
    OStreamRedirector osr{std::cerr, std::cout};

    XmlFileFormat xml{};
    DoxygenCheck dc{xml};
    dc.add_invalid_tag_value("name", "<full name and student nr>");
    const std::string file{""
                                   "//! @brief\n"
                                   "//!\n"
                                   "//! @version 1.0\n"
                                   "//!\n"
                                   "void foo(){}\n"
                                   "\n"
                                   "\n"
                                   "//! Does nothing useful\n"
                                   "//! Even more useless than an immediate return.\n"
                                   "//! @version 2.3"
                                   "void bar(){}\n"
                                   "\n"
                                   "\n"
                                   "//! Foobar\'s description\n"
                                   "void Foobar(){}"};

    EXPECT_FALSE(dc.check_brief(file));
    dc.inspect(file);
#ifdef SHOW_RESULTS
    std::cout << "== Start of file ==" << std::endl;
    for (const auto & i : xml.get_xml_data()) {
        std::cout << i << std::endl;
    }
    std::cout << "== End of file ==" << std::endl;
#endif // SHOW_RESULTS
}
