#include <limits.h>
#include "gtest/gtest.h"
#include "../source/include/CommandLineOptions.hpp"
#include "../source/include/FileSearcher.hpp"



int main(int argc, char* argv[]) {
    cout << "Starting tests" << endl;
    //CommandLineOptions(argc, argv);
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}