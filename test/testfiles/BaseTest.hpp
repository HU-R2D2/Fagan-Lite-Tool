//
// Created by Ferdi on 09-May-16.
//

#ifndef FAGAN_BASETEST_HPP
#define FAGAN_BASETEST_HPP

#include "XmlFileFormat.hpp"
class BaseTest {
public:
    BaseTest(XmlFileFormat& current_xml) : current_xml{current_xml}{}
    virtual void inspect() = 0;
    // virtual void inspect_and_fix();
    const bool is_valid() { return test_failed; }
protected:
    XmlFileFormat& current_xml;
    bool test_failed = true;
};


#endif //FAGAN_BASETEST_HPP