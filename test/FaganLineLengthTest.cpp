//
// Created by fstoeltie on 4/19/16.
//

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../source/include/LineLength.hpp"
/*
wrong comment

*/
using namespace std;
TEST(FaganFeature, LineLength)  {
    XmlFileFormat xmlf;
    vector<string> fileformat;
    fileformat.push_back("ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n");
/*    string fileformat("ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n"
                            "test \n"
                            "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n");*/
    {
        LineLength ll(xmlf);
        ll.inspect(fileformat[0]);
        ASSERT_FALSE(ll.is_valid()) << "Linelength returned true where false was expected!";
    }
    {
        fileformat.pop_back();
        fileformat.push_back("test");
        LineLength ll(xmlf);
        ll.inspect(fileformat[0]);
        cout << "Faganfeature linelength start" << endl;
        ASSERT_TRUE(ll.is_valid()) << "Linelength returned false where true was expected!";
    }
}