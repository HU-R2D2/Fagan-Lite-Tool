//
// Created by Ferdi on 10-May-16.
//

#ifndef FAGAN_CORRECTCOMMENTSTEST_HPP
#define FAGAN_CORRECTCOMMENTSTEST_HPP


class CorrectCommentsTest : public BaseTest {
public:
    CorrectCommentsTest(XmlFileFormat& current_xml, std::vector<std::string> & f_contents);
    void inspect();
private:
    std::vector<std::string> f_contents;
};


#endif //FAGAN_CORRECTCOMMENTSTEST_HPP
