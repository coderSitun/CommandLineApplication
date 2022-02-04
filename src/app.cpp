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

void App::cli(){
}

void App::execute(){
    while(this->appRun){
        while(!commands.empty()){
            std::vector<std::string> parts = parse(commands.front());
            switch(getCommandType(parts[0]))
            {
                case ADD:
                case SUBTRACT:
                case MULTIPLY:
                case DIVIDE:
                default:;
            }
            commands.pop();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}