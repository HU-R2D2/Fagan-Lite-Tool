//
// Created by Matthijs on 8-4-2016.
//
//TODO: implement tests.
#include <gtest/gtest.h>
#include "../source/include/HeaderCheck.hpp"

using namespace r2d2;
TEST(HeaderCheck, Inpect) {
    XmlFileFormat xml{};
    HeaderCheck hc{xml};
    hc.set_current_file("Test.hpp");
    hc.open_header("../Temp.txt");
    std::string temp = "//! <HEADER_VERSION 1993 03 25>";
    hc.inspect_and_fix(temp);
    std::cout << xml.data();
    //std::cout << temp << std::endl;
}