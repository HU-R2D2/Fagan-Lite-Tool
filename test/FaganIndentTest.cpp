//
// Created by Matthijs on 6-6-2016.
//

#include "gtest/gtest.h"
#include "../source/include/IndentCheck.hpp"

using namespace r2d2;
TEST(IndentCheck, ALL) {

    XmlFileFormat xml;
    IndentCheck check{xml};
    EXPECT_TRUE(check.inspect("")) << "Inspection failed";
}