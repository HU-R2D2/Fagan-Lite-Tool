//
// Created by Ferdi on 10-May-16.
//

#ifndef FAGAN_CORRECTCOMMENTSTEST_HPP
#define FAGAN_CORRECTCOMMENTSTEST_HPP


#include "BaseTest.hpp"

class CommenStyle : public BaseTest {
public:
    explicit CommenStyle(XmlFileFormat& current_xml);
    bool inspect(const std::string & file_contents) override;
    bool inspect_and_fix(std::string & file_contents){return false;}
private:
};


#endif //FAGAN_CORRECTCOMMENTSTEST_HPP
