////
// \project Roborescue
// \package r2d2
//
// \file DoxygenTool.cpp
// \date Created: <dd-mm-yy>
// \version <0.0.0>
//
// \author <full name and student nr>
//
// \section LICENSE
// License: newBSD
//
// Copyright © 2016, HU University of Applied Sciences Utrecht.
// All rights reserved.
//
// Redistribution and use in source and binary forms,
// with or without modification, are permitted provided that
// the following conditions are met:
// - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// - Neither the name of the HU University of Applied Sciences Utrecht
//   nor the names of its contributors may be used to endorse or promote
//   products derived from this software without specific prior written
//   permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////

#include "../include/DoxygenTool.hpp"
#include <iostream>
#include <regex>

namespace r2d2 {

    r2d2::DoxygenTool::DoxygenTool() {

    }

    const std::string DoxygenTool::get_author(const std::string &file) const {
        return get_annotated(file, "author");
    }

    const std::string DoxygenTool::get_date(const std::string &file) const {
        return get_annotated(file, "date");
    }

    const std::string DoxygenTool::get_version(const std::string &file) const {
        return get_annotated(file, "version");
    }

    const std::string DoxygenTool::get_annotated(const std::string &section,
                                                 const std::string &annotation) const {
        std::string result{};

        // Since a backslash and at-sign could indicate the start of an
        // annotation, "[\\\\@]" is used. If a backslash should be matched in
        // a regex, it should be preceded by a backslash. The same applies for
        // the compiler; hence the quadruple backslash. "\\s" is used to match a
        // whitespace character.
        const std::string annotated_value_regex
                = "([\\\\@]" + annotation + "\\s)"
                  // Match any number of words until the next
                  + "([\\s\\S]*?"
                  + "((\r?\n[ \t]*\\*?){2,}|)?\\*/";

        std::regex{"(/\\*|)" + annotation + " [\\s\\S]"};


        //\/\\*\\*?([\s\S]*?)(([\\@]author)([\s\S]*?))\*\/
        // TODO: remove above, and replace with something else.
        std::regex{"/\\*([\\s\\S]*?)(([\\\\@]" + annotation +
                   ")([\\s\\S]*?))\\*/"};
        std::string word;
#ifdef DONT_COMPILE
        while (section >> word) {
            // The '\\' and '@' indicate a Doxygen field.
            if (word == ("\\" + annotation) || word == ("@" + annotation)) {
                std::getline(section, result);
                return result;
            }
        }
#endif // DONT_COMPILE
        return result;
    }

    const std::vector<std::string> DoxygenTool::get_blocks(
            const std::string &file) const {
        std::string temp{file};
        std::vector<std::string> comment_blocks{};
        try {
            std::regex regex{
                    "" // Continue on next line.
                            // Match a block of multiple single line comments.
                            // By starting with "[\t ]*", indented lines can
                            // also be matched.
                            // "[\\S\t ]*" is used to find printable characters
                            // and single line whitespace.
                            // A non-comment line specifies the end of a block.
                            // This could either be an empty line, or 'runnable'
                            // code.
                            "(([\t ]*//(!|/)[\\S\t ]*((\r?\n)|\\0))+)"

                            "|" // Supply an alternative way to define blocks.

                            // Match a comment block which is specified as /* */
                            // Any number of characters is allowed between the
                            // opening and closing sequence.
                            "(/\\*\\*[\\s\\S]*?\\*/)"
            };
            std::smatch match{};
            // A file could match the search pattern multiple times.
            // Keep trying to find matches until no more matches are found.
            while (std::regex_search(temp, match, regex)) {
                comment_blocks.push_back(match.str());

                // Ignore the part which was just scanned.
                // The loop would otherwise not end, as the same match is found.
                temp = match.suffix().str();
            }

        } catch (std::regex_error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return comment_blocks;
    }

    const std::vector<std::string> DoxygenTool::get_authors(
            const std::string &file) const {
        return std::vector<std::string>();
    }
}
#ifdef DONT_COMPILE
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
#endif