// ++--++ #version 8416
// @file <main.cpp>          
// @date Created: <07-04-16>
// @version <1.0>       
// @author <Bob Dillen>           
//
// @section LICENSE
// License: newBSD
//
// Copyright © 2016, HU University of Applied Sciences Utrecht.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ++--++

/**
	ToDo, add classes to this tool and perhaps even a namespace.
	Rewrite variables accordingly to the coding standards.
	Link Header authors to cpp authors.
	change all indent tabs to spaces
	Document everything.
	Add Linux support (but ofcourse).
	~Drink tea.
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <sstream>
#include "../include/FileSearcher.hpp"
#include "../include/CommandLineOptions.hpp"
#include "../include/FaganInspectionTest.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    cout << "test everywhere" << endl;

    CommandLineOptions CLO(argc, argv);
    cout << "CLO.cmdOptions[Commands::DIRECTORY] " << CLO.cmdOptions[Commands::DIRECTORY];
    FileSearcher fs(CLO.cmdOptions[Commands::DIRECTORY]);

    FaganInspectionTest FIT(fs.get_files());

    string t_file;
    /*   if (argc == 1)
           t_file = "template.txt";SOURCES
       else {
           const char *templateFile = argv[1];
           t_file = templateFile;
       }
       cout << "template file is: " << t_file << endl;

       FileSearcher testSearcher;
       testSearcher.getFiles("nothing", "emp", "test", "moretest");*/
    /*std::ifstream ifs(t_file);
    std::string template_content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
    ifs.close();
    cout << template_content;

    for (string& str : getSubDirectories("../"))	{
        string filled_template = template_content;
        cout << "Writing into file... " << str << endl;
        ofstream oFile(str + "format");
        ifstream iFile(str);
        std::string hpp_content( (std::istreambuf_iterator<char>(iFile) ),
                                (std::istreambuf_iterator<char>()    ) );
        validateTemplateVersion(filled_template, hpp_content);
        changeAuthor(filled_template, hpp_content);
        changeDate(filled_template, hpp_content);
        changeVersion(filled_template, hpp_content);
        changeFileName(filled_template, str);
        std::size_t found = hpp_content.find("++--++");
        if(found == string::npos)	{
            oFile << filled_template << endl; // write template
            oFile << hpp_content;
            iFile.close();
            oFile.close();
            string f1 = str + "format";
            string f2 = str + "renamed";
              if( remove( str.c_str() ) != 0 )
                perror( "Error deleting file" );
              else
                puts( "File successfully deleted" );
            rename(f1.c_str(), str.c_str());
        }
        else {
            iFile.close();
            oFile.close();
            if( remove( (str + "format").c_str() ) != 0 )
                perror( "Error deleting file" );
              else
                puts( "File successfully deleted" );
        }
    }*/
    // Read template file
    return 0;
}