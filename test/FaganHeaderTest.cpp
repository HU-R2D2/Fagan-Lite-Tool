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
    hc.open_header("C:\\Users\\Matthijs\\Desktop\\Temp.txt");
    std::string temp = "//! @author Sierra Tango";
    hc.inspect_and_fix(temp);
    std::cout << temp << std::endl;
}