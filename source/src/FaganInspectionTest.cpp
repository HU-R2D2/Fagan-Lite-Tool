//
// Created by Ferdi on 09-May-16.
//

#include "../include/FaganInspectionTest.hpp"
#include "../include/LineLength.hpp"
#include "../include/CommentStyle.hpp"
#include "../include/InclusionGuards.hpp"
#include "../include/DoxygenCheck.hpp"
#include "../include/IndentCheck.hpp"

#include "../include/HeaderCheck.hpp"
#include <fstream>
#include <regex>



FaganInspectionTest::FaganInspectionTest(std::vector<std::string> fileLocations,
                                         CommandLineOptions& CLO) : CLO{CLO} {
    //run_all_inspections(fileLocations);
    if(CLO.cmdOptions[Commands::INSPECTION_TYPE].find("inspect-only") !=
            CLO.cmdOptions[Commands::INSPECTION_TYPE].npos)  {
        std::cout << "running inspections only" << std::endl;
        run_all_inspections(fileLocations);
    }
    else if(CLO.cmdOptions[Commands::INSPECTION_TYPE].find("inspect-fix") !=
            CLO.cmdOptions[Commands::INSPECTION_TYPE].npos) {
        std::cout << "running inspections and if possible, will fix also" <<
                std::endl;
        run_all_inspections_and_fix(fileLocations);
    }
    else    {
        std::cout << "unknown inspection type in program argument list, "
                             "ending program" << std::endl;
    }

}


void FaganInspectionTest::run_all_inspections(std::vector<std::string>
                                              fileLocations) {

    //ToDo Clean up the code within this method
    XmlFileFormat xmlff{};
    auto root = std::shared_ptr<XmlNode>(new XmlNode("root"));
    root->add_attribute("xml:space", "preserve");

    std::fstream fs(CLO.cmdOptions[Commands::OUTPUT_FILE], std::ios_base::out);
    fs << "<?xml version=\"1.0\" encoding=\"utf-8\"?>";

    for (std::string fpath : fileLocations) {
        std::cout << "Running inspections on file: " << fpath << std::endl;
        XmlFileFormat xmlff;
        std::shared_ptr<XmlNode> file_node = std::shared_ptr<XmlNode>
                (new XmlNode("file"));
        file_node->add_attribute("file_name", fpath);
        root->add_child_node(file_node);

        xmlff.base_node = file_node;
        /*xmlff.add_base_node("file", fpath);*/
        std::vector<BaseTest *> tests;
        r2d2::DoxygenCheck dc{xmlff};
        tests.push_back(&dc);

        r2d2::IndentCheck ic{xmlff};
        tests.push_back(&ic);

        LineLength ll(xmlff);
        tests.push_back(&ll);

        CommentStyle cs(xmlff);
        tests.push_back(&cs);

        std::string f_content = get_file_contents(fpath.c_str());

        r2d2::HeaderCheck hc{xmlff};
        try {
            hc.open_header(CLO.cmdOptions[Commands::TEMPLATE]);

            auto last_index = fpath.find_last_of("/");
            if(last_index != fpath.npos)    {
                hc.set_current_file(fpath.substr(last_index + 1));
            }
            tests.push_back(&hc);
        } catch (...) {
            // Skip this test if it failed to open the header.
            // The error should be thrown from "open_header" which, as a result,
            // does not add it to the test set. Catch being mandatory for the try.
            std::cerr << "Failed to open header file." << std::endl;
        }


        for (const auto &test : tests) {
            test->inspect(f_content);
        }
    }
    xmlff.base_node = root;
    std::cout << xmlff.data();

}
void FaganInspectionTest::run_all_inspections_and_fix(std::vector<std::string>
                                                      fileLocations) {
    //ToDo Clean up the code within this method
    XmlFileFormat xmlff{};
    auto root = std::shared_ptr<XmlNode>(new XmlNode("root"));
    root->add_attribute("xml:space", "preserve");
    //std::vector<BaseTest *> tests;

    std::fstream fs(CLO.cmdOptions[Commands::OUTPUT_FILE], std::ios_base::out);
    fs << "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
    for (std::string fpath : fileLocations) {
        std::vector<BaseTest *> tests;
        std::cout << "Running inspections on file: " << fpath << std::endl;
        XmlFileFormat xmlff;
        std::shared_ptr<XmlNode> file_node = std::shared_ptr<XmlNode>
                (new XmlNode("file"));
        file_node->add_attribute("file_name", fpath);
        root->add_child_node(file_node);

        xmlff.base_node = file_node;

        r2d2::DoxygenCheck dc{xmlff};
        tests.push_back(&dc);

        r2d2::IndentCheck ic{xmlff};
        tests.push_back(&ic);

        LineLength ll(xmlff);
        tests.push_back(&ll);

        CommentStyle cs(xmlff);
        tests.push_back(&cs);

        r2d2::HeaderCheck Hc(xmlff);
        tests.push_back(&Hc);
        uint32_t last_index = 0;
        Hc.open_header(CLO.cmdOptions[Commands::TEMPLATE]);
        if((last_index = fpath.find_last_of("/")) != fpath.npos)    {
            Hc.set_current_file(fpath.substr(last_index + 1));
        }
        std::string f_content = get_file_contents(fpath.c_str());
        cs.inspect_and_fix(f_content);

        for(const auto & test : tests) {
            try {
                //test->inspect(f_content);
                test->inspect_and_fix(f_content);
            } catch (...) {
                std::cerr << "Exception during test." << std::endl;
            }
        }

        if (fpath.find(".hpp") != fpath.npos) {
            InclusionGuards IG(xmlff);
            IG.inspect(f_content);
        }
        std::remove((fpath + "test").c_str());
        std::fstream fs2((fpath + "test").c_str(), std::ios_base::out);
        fs2 << f_content;
        fs2.close();
        //xmlff.add_xml_data("</file>\n");
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