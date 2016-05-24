//
// Created by Ferdi on 11-May-16.
//

#ifndef FAGAN_INCLUSIONGUARDS_HPP
#define FAGAN_INCLUSIONGUARDS_HPP

#include "BaseTest.hpp"
class InclusionGuards : public BaseTest{
public:
    InclusionGuards(XmlFileFormat& current_xml);
    bool inspect(const std::string & file_contents) override;
    bool inspect_and_fix(std::string & file_contents){return false;}
private:
};


#endif //FAGAN_INCLUSIONGUARDS_HPP
