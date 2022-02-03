#include"app.hpp"
#include<thread>
#include<chrono>

void App::run(){
    this->appRun = true;
    std::thread commandLine(this->cli);
    std::thread executer(this->execute);

    commandLine.join();
    executer.join();
}

void App::cli(){
}

void App::execute(){
    while(this->appRun){
        while(!commands.empty()){
            std::vector<std::string> parts = parse(commands.front());

            commands.pop();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}