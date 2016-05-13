//
// Created by Matthijs on 8-4-2016.
//
#include <sstream>
#include "gtest/gtest.h"
#include "../source/include/DoxygenTool.hpp"
#include "../source/include/DoxygenCheck.hpp"


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
    for (const auto & author : author) {
        std::cout << "Author: " << std::endl << author << std::endl;
    }
#endif
}

TEST(DoxygenCheck, all) {

    // Make sure that when an exception occurs, the streams are returned to how
    // they originally were. It could otherwise give strange results.
    struct StreamRedirection {
    private:
        std::streambuf *temp;
    public:
        StreamRedirection() : temp {std::cerr.rdbuf()} {
            std::cerr.rdbuf(std::cout.rdbuf());
        }
        ~StreamRedirection() {
            std::cerr.rdbuf(temp);
        }
    } stream_redirection;

    DoxygenCheck dc{};
    dc.add_invalid_tag_value("name", "<full name and student nr>");
    const std::string file{""
                                   "//! @brief\n"
                                   "//!\n"
                                   "//!\n"
                                   "//!\n"
                                   "void foo(){}\n"
                                   "\n"
                                   "\n"
                                   "//! Does nothing useful\n"
                                   "//! Even more useless than an immediate return.\n"
                                   "void bar(){}\n"
                                   "\n"
                                   "\n"
                                   "//! Foobar\'s description\n"
                                   "void Foobar(){}"};

    EXPECT_FALSE(dc.check_brief(file));
}

TEST(DoxygenCheck, name) {
    std::cerr << "Hello" << std::endl;
}