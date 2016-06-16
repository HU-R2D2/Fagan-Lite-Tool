// ++--++ #version 8416
// @file <main.cpp>          
// @date Created: <07-04-16>
// @version <1.0>       
// @author <Ferdi Stoeltie>
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
#include <vector>
#include "../include/FileSearcher.hpp"
#include "../include/CommandLineOptions.hpp"
#include "../include/FaganInspectionTest.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    CommandLineOptions CLO(argc, argv);

    cout << "CLO.cmdOptions[Commands::DIRECTORY] " <<
    CLO.cmdOptions[Commands::DIRECTORY] << endl;

    FileSearcher fs(CLO.cmdOptions[Commands::DIRECTORY]);

    FaganInspectionTest FIT(fs.get_files(), CLO);


    // Read template file

    char c;
    std::cin >> c;

    return 0;
}
