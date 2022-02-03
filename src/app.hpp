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
        DIVIDE
    };
    bool appRun;
    std::queue<std::string> commands;
    std::vector<std::string> parse(std::string commandWithArgs);
    CommandType getCommandType(std::string command);
public:
    void run();
    void cli();
    void execute();
};

#endif