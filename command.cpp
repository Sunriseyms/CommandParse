#include "command.h"
#include <algorithm>
#include <bits/getopt_core.h>
#include <iostream>
#include <functional>
#include <memory>

CommandDeletedUinquePtr FindCommand(const char* name, const std::vector<Command>& commands) {
    if (name == nullptr) {
        return nullptr;
    }
    auto it = std::find_if(commands.begin(), commands.end(), [&name](auto& elem) {
        return elem.name == name;
    });

    if (it == commands.end()) {
        return nullptr;
    }
    return CommandDeletedUinquePtr(const_cast<Command*>(&(*it)), [](auto command){});
}


int DispatchCommand(int argc, char** argv, const Commands& verbs) {
    int left;

    left = argc - optind;
    argc += optind;
    optind = 0;
    const char *name = argv[optind];
    CommandDeletedUinquePtr command = FindCommand(name, verbs);
    if (!command) {
        // TODO: cout error message, print help msg?
        return -1;
    }

    if ((command->min_args != kAnyArgs) && (left < command->min_args)) {
        std::cout << "Too few arguments." << std::endl;
        return -1;
    }

    if ((command->max_args != kAnyArgs) && (left > command->max_args)) {
        std::cout << "Too many arguments." << std::endl;
        return -1;
    }

    return command->dispatch(argc, argv);

}