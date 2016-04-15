//
// Created by Matthijs on 8-4-2016.
//
#include <sstream>
#include "gtest/gtest.h"
#include "../source/include/DoxygenTool.hpp"


using namespace r2d2;

TEST(HeaderTool, other) {
    std::stringstream test_case{""};
    test_case << "@author Wim" << std::endl;
    test_case << "\\author Pierre" << std::endl;

    //
    DoxygenTool tool;
    EXPECT_EQ("", tool.get_author(test_case.str()));
    EXPECT_EQ("", tool.get_date(test_case.str()));
    EXPECT_EQ("", tool.get_version(test_case.str()));
}