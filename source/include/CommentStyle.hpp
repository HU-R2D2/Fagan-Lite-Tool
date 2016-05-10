//
// Created by Ferdi on 10-May-16.
//

#ifndef FAGAN_CORRECTCOMMENTSTEST_HPP
#define FAGAN_CORRECTCOMMENTSTEST_HPP


#include "BaseTest.hpp"

class CommenStyle : public BaseTest {
public:
    CommenStyle(XmlFileFormat& current_xml, std::vector<std::string> & f_contents);
    void inspect();
private:
    std::vector<std::string> f_contents;
};


#endif //FAGAN_CORRECTCOMMENTSTEST_HPP
