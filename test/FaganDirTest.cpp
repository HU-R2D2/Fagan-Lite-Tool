#include <limits.h>
#include <gtest/gtest.h>
#include <iostream>
#include "../source/include/FileSearcher.hpp"

using namespace std;
// test will be written in the future due to folder dependenc of the filesearcher
TEST(DIRTESt, DIRTEST)  {
    cout << endl << "Reading dir structure" << endl;
    FileSearcher fs1("../");
    for( auto file : fs1.get_files())
    cout << file << endl;
    cout << endl << "End of reading dir structure" << endl;
}