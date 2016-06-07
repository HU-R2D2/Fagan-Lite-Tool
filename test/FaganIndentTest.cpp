//
// Created by Matthijs on 6-6-2016.
//

#include "gtest/gtest.h"
#include "../source/include/IndentCheck.hpp"

using namespace r2d2;
TEST(IndentCheck, ALL) {

    XmlFileFormat xml;
    IndentCheck check{xml};
    std::string value{""
                              "namespace r2d2 {\n"
                              "    class thingy {\n"
                              "  \tthingy() {\n"
                              "            \t//TODO: implement\n"
                              "    };\n"
                              "}\n"};
    check.inspect_and_fix(value);
    std::cout << value;
    EXPECT_EQ("     \t     Hello", value);
    EXPECT_TRUE(check.inspect(value)) << "Inspection failed";

    std::cout << "== XML File ==" << std::endl;
    for (const auto & line : xml.get_xml_data()) {
        std::cout << line;
    }
    std::cout << "== XML File ==" << std::endl;
}