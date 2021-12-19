#include <bits/getopt_core.h>
#include <iostream>
#include <unistd.h>
#include "command.h"

int Set(int argc, char** argv) {
    std::cout << "Set command, argc:" << argc << std::endl; 
    return 0;
}

int Get(int argc, char** argv) {
    std::cout << "Get command, argc:" << argc << std::endl; 
    return 0;
}

int main(int argc, char** argv) {
    const Commands commands = {
        {"set", 2, 2, Set},
        {"get", 1, 1, Get},
    };

    auto command = FindCommand(argv[optind], commands);
    if (!command) {
        if (argv[optind]) {
            std::cout << "No " << argv[optind] << " this command." << std::endl;
        } else {
            std::cout << "No args input,Please input args" << std::endl;
        }
        return -1;
    }
    return command->dispatch(argc, argv);
}
