#include<iostream>
#include"app.hpp"

int main(){
    std::cout << "Starting Application..." << std::endl;
    App *app = new App();
    app->run();
    std::cout << "Exiting Application!" << std::endl;
    return 0;
}