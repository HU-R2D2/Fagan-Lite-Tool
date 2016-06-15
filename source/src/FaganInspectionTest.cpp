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
#include "../include/HeaderCheck.hpp"
#include <fstream>
#include <bits/unique_ptr.h>

using namespace std;

FaganInspectionTest::FaganInspectionTest(vector<string> fileLocations) {

    run_all_inspections(fileLocations);
}

void FaganInspectionTest::run_all_inspections(vector<string> fileLocations) {
    //ToDo Clean up the code within this method
    XmlFileFormat xmlff{};
    auto root = std::shared_ptr<XmlNode>(new XmlNode("root"));
    root->add_attribute("xml:space", "preserve");
    fstream fs("E:\\Development\\HBO\\Year2\\BlokC\\ThemaOpdracht7-8\\Fagan-Lite-Tool\\testfile.xml", ios_base::out);
    fs << "<?xml version=\"1.0\" encoding=\"utf-8\"?>";

    std::vector<BaseTest *> tests;
    r2d2::DoxygenCheck dc{xmlff};
    tests.push_back(&dc);

    r2d2::IndentCheck ic{xmlff};
    tests.push_back(&ic);

    r2d2::HeaderCheck hc{xmlff};
    hc.open_header("../Temp.txt");
    tests.push_back(&hc);

    LineLength ll(xmlff);
    tests.push_back(&ll);

    CommentStyle cs(xmlff);
    tests.push_back(&cs);


    for (std::string fpath : fileLocations) {
        cout << "Running inspections on file: " << fpath << endl;
        shared_ptr<XmlNode> file_node = shared_ptr<XmlNode>(new XmlNode("file"));
        file_node->add_attribute("file_name", fpath);
        root->add_child_node(file_node);

        xmlff.base_node = file_node;

        xmlff.add_xml_data(fpath);

        string f_content = get_file_contents(fpath.c_str());

        for(const auto & test : tests) {
            try {
                test->inspect(f_content);
            } catch (...) {
                std::cerr << "Exception during test." << std::endl;
            }
        }

        if (fpath.find(".hpp") != fpath.npos) {
            InclusionGuards IG(xmlff);
            IG.inspect(f_content);
        }
        xmlff.add_xml_data("</file>\n");
    }

    xmlff.base_node = root;
    std::cout << xmlff.data();
    fs << xmlff.data();
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