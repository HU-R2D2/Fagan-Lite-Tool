//
// Created by fstoeltie on 4/15/16.
//

#ifndef FAGAN_COMMANDLINEOPTIONS_HPP
#define FAGAN_COMMANDLINEOPTIONS_HPP
#include <iostream>
#include <vector>
#include <map>

enum class Commands : uint16_t {
    INSPECTIONS,
    DIRECTORY,
};
class CommandLineOptions {
public:
    CommandLineOptions(int argc, char* argv[]);
    CommandLineOptions()= default;
    std::string getCommand(unsigned int i);
    std::map<Commands, std::string> cmdOptions; // development only
private:

    void checkInspections();
    bool checkDirectory();
    std::vector<std::string> cmds;

};


#endif //FAGAN_COMMANDLINEOPTIONS_HPP
