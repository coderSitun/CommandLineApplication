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
        TOTAL_COMMANDS
    };
    bool appRun;
    std::queue<std::string> commands;
    std::vector<std::string> parse(std::string commandWithArgs);
    CommandType getCommandType(std::string command);
    void cli();
    void execute();
public:
    void run();
};

#endif