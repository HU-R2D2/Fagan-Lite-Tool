//
// Created by Matthijs on 8-4-2016.
//
#include <sstream>
#include "gtest/gtest.h"
#include "../source/include/DoxygenTool.hpp"


using namespace r2d2;

TEST(DoxygenTool, other) {
    std::stringstream test_case{""};
    test_case << "//! @author Wim" << std::endl;
    test_case << "//! \\author Pierre" << std::endl;

    DoxygenTool tool;
    std::vector<std::string> comments = tool.get_blocks(test_case.str());
    std::cout << comments.size() << std::endl;
    for (auto comment : comments) {

        std::cout << comment << std::endl;
        if (comment == "//") {

        }
    }
#ifdef DONT_COMPILE
    // Since there is no way to check a name matches that of the author,
    // something different needs to be tested. In this case a check is performed
    // which indicates the values are different than the values supplied by default.
    // Other than that
    EXPECT_EQ("<1.0>", tool.get_author(test_case.str()));
    EXPECT_EQ("h", tool.get_date(test_case.str()));
    EXPECT_EQ("i", tool.get_version(test_case.str()));
#endif
}