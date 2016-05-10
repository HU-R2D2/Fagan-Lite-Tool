//
// Created by Ferdi on 11-May-16.
//

#ifndef FAGAN_INCLUSIONGUARDS_HPP
#define FAGAN_INCLUSIONGUARDS_HPP

#include "BaseTest.hpp"
class InclusionGuards : public BaseTest{
public:
    InclusionGuards(XmlFileFormat& current_xml, std::vector<std::string> & f_contents);
    void inspect();
private:
    std::vector<std::string> f_contents;
};


#endif //FAGAN_INCLUSIONGUARDS_HPP
