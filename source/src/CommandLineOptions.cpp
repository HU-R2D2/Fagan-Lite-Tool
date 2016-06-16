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
    if(checkInspection("config_file=", Commands::CONFIG_FILE))   {
        std::fstream fs(CommandLineOptions::cmdOptions[Commands::CONFIG_FILE],
                        std::ios_base::in);
        // get config file contents
        while(!fs.eof())    {
            std::string s;
            fs >> s;
            cmds.push_back(s);
        }
    }
    if(!checkInspection("base_directory=", Commands::DIRECTORY))    {
        std::cout << "could not find directory" << std::endl;
        cmdOptions[Commands::DIRECTORY] = "";
    }

    if(!checkInspection("output_file=", Commands::OUTPUT_FILE))   {
        CommandLineOptions::cmdOptions[Commands::OUTPUT_FILE] = "results.xml";
    }

}
bool CommandLineOptions::checkInspection(std::string find_keyword, Commands type)   {
    for (std::vector<std::string>::iterator i = cmds.begin(); i < cmds.end(); i++) {
        if ((*i).find(find_keyword) != (*i).npos) {
            CommandLineOptions::cmdOptions[type] = (*i).
                    erase(0, find_keyword.size());
            cmds.erase(i);
            return true;
        }
    }
    return false;
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
