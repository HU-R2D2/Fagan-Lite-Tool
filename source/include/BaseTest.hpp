//
// Created by Ferdi on 09-May-16.
//

#ifndef FAGAN_BASETEST_HPP
#define FAGAN_BASETEST_HPP

#include "XmlFileFormat.hpp"
// @author Ferdi Stoeltie
// @date 11-05-16
// @brief This is the base class for all tests. It provides two methods (inspect and inspect_and_fix).
//          These methods can be used to run the fagan test and only inspect or inspect and fix where possible.
//          Other than these two methods, it contains a reference to a XmlFileFormat object to write its results to.
// @warning This class is only meant to be inherited from!
class BaseTest {
public:
    //! @brief Constructor taking in a XmlFileFormat and storing the reference.
    //! @param current_xml A reference to a XmlFileFormat object. It will write its test results to this.
    explicit BaseTest(XmlFileFormat& current_xml) : current_xml{current_xml}{}

    //! @brief Virtual method that will be overwritten to contain the fagan inspection tests.
    //!
    //! @param file_contents contents of the file to inspect.
    //! @return True indicates found deviations from standard do not exist.
    //! @warning Pure method!
    virtual bool inspect(const std::string & file_contents) = 0;

    //! @brief Virtual method that will be overwritten to contain the fagan inspection tests,
    //! and fix the issues wherever possible.
    //!
    //! @param file_contents Contents of the file to inspect and possibly change.
    //! @return True indicates found deviations from standard do not exist
    //! after performing possible fixes.
    //! @warning Pure method!
    virtual bool inspect_and_fix(std::string & file_contents) = 0;

    //! @brief Returns the boolean that contains the result that is stored by running inspect OR inspect_and_fix.
    //!          Should only be checked after running inspect OR inspect_and_fix, otherwise it is always false.
    //! @return Returns true if the test has run succesful and false otherwise.
    //! @warning Only use after running one of the fagan inspection test methods (inspect, inspect_and_fix).
    const bool is_valid() { return test_is_valid; }
protected:
    XmlFileFormat& current_xml; // Reference to the XMlFileFormat object, to write to.
    bool test_is_valid = false; // Boolean containing test resulsts.
};


#endif //FAGAN_BASETEST_HPP
