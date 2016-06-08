//
// Created by Ferdi on 09-May-16.
//

#include "../include/FaganInspectionTest.hpp"
#include "../include/FileSearcher.hpp"
#include "../include/LineLength.hpp"
#include "../include/CommentStyle.hpp"
#include "../include/InclusionGuards.hpp"
#include "../include/DoxygenCheck.hpp"
#include "../include/IndentCheck.hpp"
#include <fstream>
#include <bits/unique_ptr.h>

using namespace std;

FaganInspectionTest::FaganInspectionTest(vector<string> fileLocations) {

    run_all_inspections(fileLocations);
}

void FaganInspectionTest::run_all_inspections(vector<string> fileLocations) {
    //ToDo get all files and run all inspections on each file

    XmlFileFormat xmlff{};
    std::vector<BaseTest *> tests;

    //FileSearcher files("E:/Development/HBO/Year2/BlokC/ThemaOpdracht7-8/Fagan-Lite-Tool/test/testfiles");
    for (std::string fpath : fileLocations) {
    XmlFileFormat xmlff{};
    xmlff.add_base_node("file", fpath);
    std::vector<BaseTest *> tests;
    r2d2::DoxygenCheck dc{xmlff};
    tests.push_back(&dc);

    //r2d2::IndentCheck ic{xmlff};
   // tests.push_back(&ic);

    LineLength ll(xmlff);
    tests.push_back(&ll);

    CommentStyle cs(xmlff);
    tests.push_back(&cs);

/*    //FileSearcher files("E:/Development/HBO/Year2/BlokC/ThemaOpdracht7-8/Fagan-Lite-Tool/test/testfiles");
    for (std::string fpath : fileLocations) {
>>>>>>> 9012e3d3039f0ddb1d00b0994d59d511da72efba*/


        xmlff.add_xml_data(fpath);

        // get file contents and store in string vector
        // vector<string> file_contents = get_file_data(fpath);
        string f_content = get_file_contents(fpath.c_str());

        for(const auto & test : tests) {
            test->inspect(f_content);
        }
        std::cout << xmlff.data();
        if (fpath.find(".hpp") != fpath.npos) {
            InclusionGuards IG(xmlff);
            IG.inspect(f_content);
        }

        xmlff.add_xml_data("</file>\n");
        for (string s : xmlff.get_xml_data()) {
           // cout << s << "\n";
        }
    }
}

std::vector<std::string> FaganInspectionTest::get_file_data(string file_path) {
    ifstream iFile(file_path);
    // get file contents and store in string vector
    vector<string> file_contents;
    while (!iFile.eof()) {
        string s;
        getline(iFile, s);
        file_contents.push_back(s);
    }
    return file_contents;
}

// http://insanecoding.blogspot.nl/2011/11/how-to-read-in-file-in-c.html
std::string FaganInspectionTest::get_file_contents(const char *filename) {
    std::FILE *fp = std::fopen(filename, "rb");
    if (fp) {
        std::string contents;
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        std::fread(&contents[0], 1, contents.size(), fp);
        std::fclose(fp);
        return (contents);
    }
    throw (errno);
}