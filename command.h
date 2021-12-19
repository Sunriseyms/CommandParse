#include <limits>
#include <string>
#include <memory>
#include <vector>
#include <functional>

constexpr int kAnyArgs = std::numeric_limits<int>::max();

using DispatchFunc = std::function<int(int argc,char** argv)>;

struct Command {
    const std::string name;
    const int min_args;
    const int max_args;
    const DispatchFunc dispatch;
};

using CommandDeletedUinquePtr = std::unique_ptr<Command, std::function<void(Command*)>>;
using Commands = std::vector<Command>;

CommandDeletedUinquePtr FindCommand(const char* name, const std::vector<Command>& commands);
int DispatchCommand(int argc, char** argv, const Commands& verbs);