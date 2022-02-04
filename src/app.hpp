#ifndef __APP
#define __APP

#include<string>
#include<queue>
#include<vector>

class App{
private:
    enum CommandType{
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        HALT,
        TOTAL_COMMANDS
    };
    bool appRun;
    std::queue<std::string> commandsWithArgs;
    std::vector<std::string> parse(std::string commandWithArgs, char delim = ' ');
    CommandType getCommandType(std::string command);
    void cli();
    void execute();
    void operate(std::string commandWithArgs);
public:
    void run();
};

#endif