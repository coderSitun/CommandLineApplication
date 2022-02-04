#include"app.hpp"
#include<thread>
#include<chrono>

void App::run(){
    this->appRun = true;
    std::thread commandLine(&App::cli, this);
    std::thread executer(&App::execute, this);

    commandLine.join();
    executer.join();
}

App::CommandType App::getCommandType(std::string command){
    if(!command.compare("add"))
        return ADD;
    if(!command.compare("subtract"))
        return SUBTRACT;
    if(!command.compare("multiply"))
        return MULTIPLY;
    if(!command.compare("divide"))
        return DIVIDE;
    return TOTAL_COMMANDS;
}

void App::cli(){
}

void App::execute(){
    while(this->appRun){
        while(!commandsWithArgs.empty()){
            std::vector<std::string> parts = parse(commandsWithArgs.front());
            switch(getCommandType(parts[0]))
            {
                case ADD:
                case SUBTRACT:
                case MULTIPLY:
                case DIVIDE:
                default:;
            }
            commandsWithArgs.pop();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}