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

    if(check_program_argument("config_file=", Commands::CONFIG_FILE))   {
        std::fstream fs(CommandLineOptions::cmdOptions[Commands::CONFIG_FILE],
                        std::ios_base::in);
        // get config file contents
        while(!fs.eof())    {
            std::string s;
            fs >> s;
            cmds.push_back(s);
        }
    }
    if(!check_program_argument("base_directory=", Commands::DIRECTORY))    {
        std::cout << "could not find directory" << std::endl;
        cmdOptions[Commands::DIRECTORY] = "";
    }

    if(!check_program_argument("template_file=", Commands::TEMPLATE))    {
        std::cout << "could not find directory" << std::endl;
        cmdOptions[Commands::TEMPLATE] = "./template.txt";
    }

    if(!check_program_argument("output_file=", Commands::OUTPUT_FILE))   {
        CommandLineOptions::cmdOptions[Commands::OUTPUT_FILE] = "results.xml";
    }
    if(!check_program_argument("inspection_type=", Commands::INSPECTION_TYPE))   {
        CommandLineOptions::cmdOptions[Commands::INSPECTION_TYPE] = "inspect-only";
    }

}
bool CommandLineOptions::check_program_argument(std::string find_keyword,
                                         Commands type)   {
    for (std::vector<std::string>::iterator i = cmds.begin(); i < cmds.end();
         i++) {
        if ((*i).find(find_keyword) != (*i).npos) {
            CommandLineOptions::cmdOptions[type] = (*i).
                    erase(0, find_keyword.size());
            cmds.erase(i);
            return true;
        }
    }
    return false;
}
/*<<<<<<< HEAD

void CommandLineOptions::checkInspections() {
    for (std::vector<std::string>::iterator i = cmds.begin(); i < cmds.end();
         i++) {
        if ((*i).find("inspect-all") != (*i).npos) {
            CommandLineOptions::cmdOptions[Commands::INSPECTIONS] =
                    "inspect-all";
=======
bool CommandLineOptions::check_config_file()  {
    string cmd_string("config_file=");
    for (vector<string>::iterator i = cmds.begin(); i < cmds.end(); i++) {
        if ((*i).find("config_file=") != (*i).npos) {
            CommandLineOptions::cmdOptions[Commands::CONFIG_FILE] = (*i).erase(0, cmd_string.size());
            cmds.erase(i);
            return true;
>>>>>>> 6a4385d61edf292162a91206cbd6f9e4cf04d6ef
        }
    }
}*/
