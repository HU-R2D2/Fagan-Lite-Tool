#include <limits.h>
#include "gtest/gtest.h"
#include "../source/include/CommandLineOptions.hpp"
#include "../source/include/FileSearcher.hpp"
#include "../source/include/FaganInspectionTest.hpp"


using namespace std;
int main(int argc, char* argv[]) {
    cout << "Starting tests" << endl;
    //CommandLineOptions(argc, argv);
    FaganInspectionTest FIT;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}