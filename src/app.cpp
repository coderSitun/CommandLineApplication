#include"app.hpp"
#include<thread>
#include<chrono>
#include<iostream>

void App::run(){
    this->appRun = true;
    std::thread commandLine(&App::cli, this);
    std::thread executer(&App::execute, this);

    commandLine.join();
    executer.join();
}

void App::cli(){
    std::string input;
    do{
        std::cout << "App>>";
        getline(std::cin, input);
        if(!input.substr(0, 4).compare("exit"))
            appRun = false;
        else
            commandsWithArgs.push(input);
    }while(appRun);
}

void App::execute(){
    while(this->appRun){
        while(!commandsWithArgs.empty()){
            operate(commandsWithArgs.front());
            commandsWithArgs.pop();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

std::vector<std::string> App::parse(std::string commandWithArgs, char delim){
    std::vector<std::string> parsedStrings;
    std::string::size_type index = 0;
    std::string::size_type findPos;
    while((findPos = commandWithArgs.find(delim, index)) != std::string::npos){
        parsedStrings.push_back(commandWithArgs.substr(index, findPos - index));
        index = (findPos + 1);
    }
    parsedStrings.push_back(commandWithArgs.substr(index, commandWithArgs.length() - index));
    return parsedStrings;
}

App::CommandType App::getCommandType(std::string command){
    if(!command.compare("add"))
        return ADD;
    if(!command.compare("sub") || !command.compare("subtract"))
        return SUBTRACT;
    if(!command.compare("mul") || !command.compare("multiply"))
        return MULTIPLY;
    if(!command.compare("div") || !command.compare("divide"))
        return DIVIDE;
    if(!command.compare("hal") || !command.compare("halt"))
        return HALT;
    return TOTAL_COMMANDS;
}

void App::operate(std::string commandWithArgs){
    std::vector<std::string> parts = parse(commandWithArgs);
    switch(getCommandType(parts[0]))
    {
        case ADD:
            std::cout << parts[1] << " + " << parts[2] << " = " << atoi(parts[1].c_str()) + atoi(parts[2].c_str()) << std::endl;
            break;
        case SUBTRACT:
            std::cout << parts[1] << " - " << parts[2] << " = " << atoi(parts[1].c_str()) + atoi(parts[2].c_str()) << std::endl;
            break;
        case MULTIPLY:
            std::cout << parts[1] << " * " << parts[2] << " = " << atoi(parts[1].c_str()) + atoi(parts[2].c_str()) << std::endl;
            break;
        case DIVIDE:
            if(atoi(parts[2].c_str())){
                std::cout << parts[1] << " / " << parts[2] << " = " << atoi(parts[1].c_str()) + atoi(parts[2].c_str()) << std::endl;
            }
            else{
                std::cout << "Denominator is 0. Invalid operation!!" << std::endl;
            }
            break;
        case HALT:
            std::this_thread::sleep_for(std::chrono::seconds(atoi(parts[1].c_str())));
            std::cout << "Halted for " << parts[1] << " seconds" << std::endl;
            break;
        default:
            std::cout << "Invalid Command" << std::endl;
    }
}