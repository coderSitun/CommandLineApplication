#ifndef __APP
#define __APP

#include<string>
#include<queue>
#include<vector>

class App{
private:
    enum CommandType{
        BLANK,
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        HALT,
        TOTAL_COMMANDS
    };
    struct Properties{
        unsigned int numberOfArgs;
    };

    bool appRun;
    std::queue<std::string> commandsWithArgs;
    Properties properties[TOTAL_COMMANDS];
    std::vector<std::string> parse(std::string commandWithArgs, char delim = ' ');
    CommandType getCommandType(std::string command);
    void cli();
    void execute();
    void operate(std::string commandWithArgs);
public:
    App();
    void run();
};

#endif