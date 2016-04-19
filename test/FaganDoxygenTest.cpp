//
// Created by Matthijs on 8-4-2016.
//
#include <sstream>
#include "gtest/gtest.h"
#include "../source/include/DoxygenTool.hpp"


using namespace r2d2;

TEST(DoxygenTool, commentBlocks) {
    const auto & comment_block1 = ""
            "//! Commentblock 1\n"
            "//! @brief\n"
            "//! @param argc Number of commandline parameters.\n"
            "//! @param argv The actual parameters.\n";

    const auto & comment_block2 = ""
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

}