#include "spdlog/spdlog.h"
#include <asio.hpp>
#include "CLI11.hpp"
#include <iostream>
#include <sstream>

using namespace std;
using namespace asio::ip;

int main(int argc, char* argv[]){
    /*
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);
    
    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");
    
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("This message should be displayed..");    
    
    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    
    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");
    */
    CLI::App app("daytime_client");

    int port;
    app.add_option("-p, --port", port, "port to connect to");

    CLI11_PARSE(app, argc, argv);

    stringstream portStream;
    portStream << port;

    tcp::iostream strm{"localhost", portStream.str()};
    if (strm) { // connected
        string data;
        try{
            getline(strm, data);
        }catch(...){
            spdlog::error("Could not read data from stream");
        }
        
        cout << data << endl;
        strm.close(); 
    }else {
        spdlog::error("Could not connect to the server");
    }
}