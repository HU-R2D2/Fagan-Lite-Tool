//
// Created by fstoeltie on 4/15/16.
//

#include "../include/CommandLineOptions.hpp"
using namespace std;
CommandLineOptions::CommandLineOptions(int argc, char* argv[])  {
    for (int i = 0; i < argc; i++) {
        cmds.push_back(argv[i]);
    }

}
string CommandLineOptions::getCommand(uint index)    {
    if(index > cmds.size()); // Throw exception in the future
    return cmds[index];
}