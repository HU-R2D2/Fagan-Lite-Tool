//
// Created by Ferdi on 09-May-16.
//

#include "../include/FaganInspectionTest.hpp"
#include "../include/FileSearcher.hpp"
#include "../include/LineLength.hpp"
#include "../include/CommentStyle.hpp"
#include <fstream>

using namespace std;
FaganInspectionTest::FaganInspectionTest()  {
    //ToDo Insert all inspections to run
    run_all_inspections();
}
void FaganInspectionTest::run_all_inspections()  {
    //ToDo get all files and run all inspections on each file
    FileSearcher files("E:/Development/HBO/Year2/BlokC/ThemaOpdracht7-8/Fagan-Lite-Tool/test/testfiles");
    for(std::string fpath : files.get_files())  {
        XmlFileFormat xmlff;
        xmlff.add_xml_data(XML_DATA::BEGIN, fpath);

        // get file contents and store in string vector
        vector<string> file_contents = get_file_data(fpath);

        // linelength test:
        LineLength ll(xmlff, file_contents);
        ll.inspect();

        // Comment-style test:
        CommenStyle cs(xmlff, file_contents);
        cs.inspect();
        xmlff.add_xml_data(XML_DATA::END);
        for(string s : xmlff.get_xml_data())    {
            cout << s << "\n";
        }
    }
}
std::vector<std::string> FaganInspectionTest::get_file_data(string file_path)    {
    ifstream iFile(file_path);
    // get file contents and store in string vector
    vector<string> file_contents;
    while(!iFile.eof()) {
        string s;
        getline(iFile, s);
        file_contents.push_back(s);
    }
    return file_contents;
}