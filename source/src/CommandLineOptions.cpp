//
// Created by fstoeltie on 4/15/16.
//

#include <fstream>
#include "../include/CommandLineOptions.hpp"

CommandLineOptions::CommandLineOptions(int argc, char *argv[]) {
    // Populate the vector cmds, with the given argv
    for (int i = 0; i < argc; i++) {
        cmds.push_back(argv[i]);
    }
    // validate config file first
    if(checkConfigFile())   {

        std::fstream fs(CommandLineOptions::cmdOptions[Commands::CONFIG_FILE],
                        std::ios_base::in);
        // get config file contents
        while(!fs.eof())    {
            std::string s;
            fs >> s;
            cmds.push_back(s);
        }
    }
    if(!checkDirectory())    {
        //ToDo close program, directory is required!
    }
    if(!check_output_file())    {
        CommandLineOptions::cmdOptions[Commands::OUTPUT_FILE] = "results.xml";
    }
    checkInspections(); // if all inspections have to be run
}

void CommandLineOptions::checkInspections() {
    for (std::vector<std::string>::iterator i = cmds.begin(); i < cmds.end(); i++) {
        if ((*i).find("inspect-all") != (*i).npos) {
            CommandLineOptions::cmdOptions[Commands::INSPECTIONS] =
                    "inspect-all";
            cmds.erase(i);
        }
    }
}

bool CommandLineOptions::checkDirectory() {
    std::string cmd_string("base_directory=");
    for (std::vector<std::string>::iterator i = cmds.begin(); i < cmds.end(); i++) {
        if ((*i).find("base_directory=") != (*i).npos) {
            CommandLineOptions::cmdOptions[Commands::DIRECTORY] = (*i).
                    erase(0, cmd_string.size());
            cmds.erase(i);
            return true;
        }
    }
    return false;
}
bool CommandLineOptions::checkConfigFile()  {
    std::string cmd_string("config_file=");
    for (std::vector<std::string>::iterator i = cmds.begin(); i < cmds.end(); i++) {
        if ((*i).find("config_file=") != (*i).npos) {
            CommandLineOptions::cmdOptions[Commands::CONFIG_FILE] = (*i).
                    erase(0, cmd_string.size());
            cmds.erase(i);
            return true;
        }
    }
    return false;
}
bool CommandLineOptions::check_output_file()  {
    std::string cmd_string("output_file=");
    for (std::vector<std::string>::iterator i = cmds.begin(); i < cmds.end(); i++) {
        if ((*i).find("output_file=") != (*i).npos) {
            CommandLineOptions::cmdOptions[Commands::OUTPUT_FILE] = (*i).
                    erase(0, cmd_string.size());
            std::cout << "OUTPUT FILE:\t" <<
                    CommandLineOptions::cmdOptions[Commands::OUTPUT_FILE] <<
                    std::endl;
            cmds.erase(i);
            return true;
        }
    }
    return false;
}