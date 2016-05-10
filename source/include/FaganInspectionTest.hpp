//
// Created by Ferdi on 09-May-16.
//

#ifndef FAGAN_FAGANINSPECTIONTEST_HPP
#define FAGAN_FAGANINSPECTIONTEST_HPP

#include <vector>
#include <string>
class FaganInspectionTest {
public:
    FaganInspectionTest();
private:
    void run_all_inspections();
    std::vector<std::string> get_file_data(std::string file_path);
};


#endif //FAGAN_FAGANINSPECTIONTEST_HPP
