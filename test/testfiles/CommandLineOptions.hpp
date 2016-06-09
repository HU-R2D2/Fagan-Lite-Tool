//
// Created by fstoeltie on 4/15/16.
//

#ifndef FAGAN_COMMANDLINEOPTIONS_HPP
#include <iostream>
#include <vector>


class CommandLineOptions {
public:
    CommandLineOptions(int argc, char* argv[]);
    CommandLineOptions();
    std::string getCommand(unsigned int i);
private:
    std::vector<std::string> cmds;
};


#endif //FAGAN_COMMANDLINEOPTIONS_HPP
