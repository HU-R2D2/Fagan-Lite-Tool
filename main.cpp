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
#include <Windows.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <sstream>
using namespace std;
// ToDo Read template and insert in every folder / subdirectory
void findSubDirectoriesAndFiles(std::string dir, std::vector<std::string>& a)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile((dir + "/*").c_str(), &FindFileData);
	
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("\nFindFirstFile failed (%d)\n", GetLastError());
		return;
	}
	else
	{
		while (FindNextFile(hFind, &FindFileData))
		{
			cout << "Found File: " << FindFileData.cFileName << endl;
			string test(FindFileData.cFileName);
			std::string nextDir = dir + "/" + test;
			std::size_t endOfFileName;
			if (!(test.find(".") != std::string::npos))	{
				cout << "Found new subdirectory" << endl;
				findSubDirectoriesAndFiles(nextDir, a);
			}
			else if ((endOfFileName = nextDir.find(".hpp")) != std::string::npos)	{
				if(nextDir.length() == endOfFileName + 4)	{
					cout << "endOfFileName " << endOfFileName << endl;
					if(nextDir.find('.', endOfFileName + 2) == std::string::npos)	{
						cout << "is .hpp only" << endl;
					}
					cout << "Found hpp file" << endl;
					a.push_back(nextDir);
				}
			}
			else if ((endOfFileName = nextDir.find(".cpp")) != std::string::npos)	{
				cout << "endOfFileName " << endOfFileName << endl;
				if(nextDir.length() == endOfFileName + 4)	{
					char iOLE = nextDir.length() - 1; // index of last element
					if(nextDir.find('.', endOfFileName + 2) == std::string::npos)	{
						cout << "is .cpp only" << endl;
					}
					cout << "Found cpp file" << endl;
					a.push_back(nextDir);
				}
			}
		}
		FindClose(hFind);
	}
	//return nextDir;
}

vector<string> getSubDirectories(string dir)	{
	std::vector<std::string> files;
	std::vector<std::string> correctFiles;
	std::vector<std::string> failedFiles;
	//std::string resultString;

	findSubDirectoriesAndFiles(dir, files);
	//resultString += "\n_______________________\nLoading images into textures, FILE LOCATION[" + location + "]...\n";
	cout << "header files are: " << endl;
	for (string& str : files)
	{
		cout << str << endl;
		//if (!newTexture->loadFromFile(str));
			//failedFiles.push_back(new std::string(printFileName(str)));
	}
	return files;
}
void changeDate(string& template_content, string& file)	{
	// ToDo variables should be renamed...
	std::size_t foundDate = template_content.find("<dd-mm-yy>");
	std::size_t foundDateField = file.find("@date");
	if(foundDateField == string::npos){ // If file doesnt already contain @date field, add current date as date to file.
		time_t givenTime = time(0);
		struct tm * now = localtime( & givenTime );
		stringstream ss;
		string mDay;
		if((int)(now->tm_mday / 10) >= 1)	{
			stringstream ss0;
			ss << ( now->tm_mday + 1 );
			mDay = ss.str();
		}
		else	{
			mDay = now->tm_mday + '0'; // + 48
			mDay.insert(0, 1, '0');
		}
		string month;
		if((int)((now->tm_mon + 1) / 10) == 1)	{
			stringstream ss0;
			ss << ( now->tm_mon + 1 );
			month = ss.str();
		}
		else	{
			month = (now->tm_mon + 1) + '0'; // + 48
			month.insert(0, 1, '0');
		}
		cout << "month day is: " << mDay << endl;
		ss << "<" << mDay << "-" << month << "-" << (now->tm_year + 1900 - 2000) << ">";
		string currentDate;
		ss >> currentDate;
		template_content.replace(foundDate, 10, currentDate.c_str());
		return;
	}
	while(file.at(foundDateField) < '0' || file.at(foundDateField) > '9')	{
		++foundDateField;
	}
	string dateField = "<";
	
	while(file.at(foundDateField) != '\r' && file.at(foundDateField) != '\n' )	{
		cout << file.at(foundDateField);
		dateField += file.at(foundDateField);
		++foundDateField;
	}
	dateField += ">";
	string emptyField("          ");
	cout << "inserting date: " << dateField << endl;
	template_content.replace(foundDate, 10, emptyField.c_str());
	template_content.insert(foundDate, dateField.c_str());
	
}
void changeVersion(string& template_content, string& file)	{
	std::size_t foundVersion = template_content.find("<0.0.0>");
	std::size_t foundVersionTag = file.find("@version");
	if(foundVersionTag == string::npos){ // could not find version
		return;
	}
	
	while(file.at(foundVersionTag) < '0' || file.at(foundVersionTag) > '9')	{
		++foundVersionTag;
	}
	string versionField = "<";
	while(file.at(foundVersionTag) != '\r' && file.at(foundVersionTag) != '\n' )	{
		cout << file.at(foundVersionTag);
		versionField += file.at(foundVersionTag);
		++foundVersionTag;
	}
	versionField +=  ">";
	string emptyField("       ");
	template_content.replace(foundVersion, 10, emptyField.c_str());
	template_content.insert(foundVersion, versionField.c_str());
}
void changeAuthor(string& template_content, string& file)	{
	std::size_t foundAuthorField = template_content.find("<full name>");
	if(foundAuthorField == string::npos){
		return;
	} 
	std::size_t foundAuthorTag = file.find("@author");
	if(foundAuthorTag == string::npos){
		return;
	} 
	foundAuthorTag += 7;
	while(file.at(foundAuthorTag) < 'A' || file.at(foundAuthorTag) > 'z')	{
		++foundAuthorTag;
	}
	string authorName("<");
	uint8_t authorNameLength = 0;
	// get name
	while(file.at(foundAuthorTag) != '\r' && file.at(foundAuthorTag) != '\n' )	{
		cout << file.at(foundAuthorTag);
		authorName += file.at(foundAuthorTag);
		++authorNameLength;
		++foundAuthorTag;
	}
	cout << endl;
	authorName += ">";
	cout << "author name is: " << authorName << endl;
	string emptyField("           ");
	template_content.replace(foundAuthorField, 11, emptyField.c_str());
	template_content.insert(foundAuthorField, authorName.c_str());
	//template_content.replace(foundAuthorField, authorNameLength, authorName.c_str());
}
void removeTemplate(string& file)	{
	string t_identifier("++--++");
	std::size_t eot = file.find(t_identifier); // end of template
	eot = file.find(t_identifier, eot + t_identifier.length());
	if(eot == std::string::npos)	{
		cout << "could not find second template identifier" << endl;
		return;
	}
	else	{
		cout << "found second template identifier!" << endl; 
	}
	cout << "eot is: " << eot + t_identifier.length() << endl;
	file.erase(0, eot + t_identifier.length());
	file.erase(0, 1);
	cout << "Removed old template version..." << endl;
}
void validateTemplateVersion(string& template_content, string& file)	{
	string version_identifier("#version");
	std::size_t file_template_tag = file.find(version_identifier);
	if(file_template_tag == std::string::npos)	{ 	// if file does not contain version tag
		cout << "file does not contain template version!" << endl;
		return;
	}
	// get template in file version and store in int
	string r_file_content = file;
	r_file_content.erase(0, file_template_tag + version_identifier.length());
	stringstream ss1(r_file_content);
	int file_version;
	ss1 >> file_version;
	
	std::size_t template_version_tag = template_content.find(version_identifier);
	if(template_version_tag == std::string::npos)	{	// if template does not contain version tag
		cout << "template does not contain template version!" << endl;
		return;
	}
	
	string t_template_content = template_content;
	t_template_content.erase(0, file_template_tag + version_identifier.length());
	stringstream ss2(t_template_content);
	int template_version;
	ss2 >> template_version;
	
	cout << "template_version is: " << template_version << ", file_version is: " << file_version << endl;
	if(template_version > file_version)	{
		removeTemplate(file);
	}
		
}
void changeFileName(string& template_content, string fileName)	{
	std::size_t foundFile = template_content.find("<filename>");
	std::size_t foundName = fileName.find_last_of('/');
	string fName = "<" + fileName.substr(foundName + 1, fileName.length()) + ">";
	string emptyField("          ");
	template_content.replace(foundFile, 10, emptyField.c_str());
	template_content.insert(foundFile, fName);
	cout << "replaced string filename with " << fName << endl;
}

int main(int argc, char* argv[])
{
	string t_file;
	if(argc == 1)
		t_file = "template.txt";
	else	{
		const char* templateFile = argv[1];
		t_file = templateFile;
	}
	cout << "template file is: " << t_file << endl;
	
	std::ifstream ifs(t_file);
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
	}
	// Read template file
	return 0;
}