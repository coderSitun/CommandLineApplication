#include"app.hpp"
#include<thread>
#include<chrono>
#include<iostream>

App::App(){
    properties[BLANK]    = {0, ""};
    properties[ADD]      = {2, "add <operand1> <operand2>"};
    properties[SUBTRACT] = {2, "sub <operand1> <operand2>"};
    properties[MULTIPLY] = {2, "mul <operand1> <operand2>"};
    properties[DIVIDE]   = {2, "div <operand1> <operand2>"};
    properties[HALT]     = {1, "hal <time_in_seconds>"    };
}

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
    if(!command.compare(""))
        return BLANK;
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
    CommandType commandType = getCommandType(parts[0]);

    if(commandType >= TOTAL_COMMANDS){
        std::cerr << "Invalid Command: " << parts[0] << std::endl;
        return;
    }
    if(parts.size() <= properties[commandType].numberOfArgs){
        std::cerr << "usage: " << properties[commandType].usage << std::endl;
        return;
    }

    switch(commandType)
    {
        case BLANK:
            break;
        case ADD:
            std::cout << parts[1] << " + " << parts[2] << " = " << atoi(parts[1].c_str()) + atoi(parts[2].c_str()) << std::endl;
            break;
        case SUBTRACT:
            std::cout << parts[1] << " - " << parts[2] << " = " << atoi(parts[1].c_str()) - atoi(parts[2].c_str()) << std::endl;
            break;
        case MULTIPLY:
            std::cout << parts[1] << " * " << parts[2] << " = " << atoi(parts[1].c_str()) * atoi(parts[2].c_str()) << std::endl;
            break;
        case DIVIDE:
            if(atoi(parts[2].c_str())){
                std::cout << parts[1] << " / " << parts[2] << " = " << atoi(parts[1].c_str()) / atoi(parts[2].c_str()) << std::endl;
            }
            else{
                std::cout << "Denominator is 0. Invalid operation!!" << std::endl;
            }
            break;
        case HALT:
            std::this_thread::sleep_for(std::chrono::seconds(atoi(parts[1].c_str())));
            std::cout << "Halted for " << parts[1] << " seconds" << std::endl;
            break;            
    }
}