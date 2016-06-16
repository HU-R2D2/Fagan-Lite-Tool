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

    //TODO: This test depends on the outside world, making it unpredictable.
    try {
        hc.open_header("./template.txt");
        std::string temp = "//! <HEADER_VERSION 1993 03 25>";
        hc.inspect_and_fix(temp);
        std::cout << xml.data();
    } catch (...) {
        // Since the template header was either not found or empty,
        // it makes no sense to continue. This test however suffers from
        // issues in that things outside the program influence its results.
    }
}