//
// Created by fstoeltie on 4/15/16.
//

#include <fstream>
#include "../include/CommandLineOptions.hpp"

using namespace std;

CommandLineOptions::CommandLineOptions(int argc, char *argv[]) {
    // Populate the vector cmds, with the given argv
    for (int i = 0; i < argc; i++) {
        cmds.push_back(argv[i]);
    }
    // validate config file first
    if(checkConfigFile())   {

        fstream fs(cmdOptions[Commands::CONFIG_FILE], ios_base::in);
        // get config file contents
        while(!fs.eof())    {
            string s;
            fs >> s;
            cmds.push_back(s);
        }
    }
    if(!checkDirectory())    {
        //ToDo close program, directory is required!
    }
    checkInspections(); // if all inspections have to be run
}

void CommandLineOptions::checkInspections() {
    for (vector<string>::iterator i = cmds.begin(); i < cmds.end(); i++) {
        if ((*i).find("inspect-all") != (*i).npos) {
            cmdOptions[Commands::INSPECTIONS] = "inspect-all";
            cmds.erase(i);
        }
    }
}

bool CommandLineOptions::checkDirectory() {
    string cmd_string("base_directory=");
    for (vector<string>::iterator i = cmds.begin(); i < cmds.end(); i++) {
        if ((*i).find("base_directory=") != (*i).npos) {
            cmdOptions[Commands::DIRECTORY] = (*i).erase(0, cmd_string.size());
            cmds.erase(i);
            return true;
        }
    }
    return false;
}
bool CommandLineOptions::checkConfigFile()  {
    string cmd_string("config_file=");
    for (vector<string>::iterator i = cmds.begin(); i < cmds.end(); i++) {
        if ((*i).find("config_file=") != (*i).npos) {
            cmdOptions[Commands::CONFIG_FILE] = (*i).erase(0, cmd_string.size());
            cmds.erase(i);
            return true;
        }
    }
    return false;
}