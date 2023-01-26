#include "timeutils.h"
#include "CLI11.hpp"
#include "spdlog/spdlog.h"
#include <iostream> 
#include <asio.hpp>
#include <chrono>

using namespace std; 
using namespace asio::ip;

int main(int argc, char* argv[]) {
    CLI::App app("daytime_server");

    short unsigned int port;
    app.add_option("-p, --port", port, "server port");

    CLI11_PARSE(app, argc, argv);
    
    while(true){
        try{
            asio::io_context ctx;
            tcp::endpoint ep{tcp::v4(), port};
            tcp::acceptor acceptor{ctx, ep};
            acceptor.listen();

            tcp::socket sock{ctx};
            acceptor.accept(sock);
            tcp::iostream strm{std::move(sock)};

            try{
                TIME_UTILS_H::operator<<(strm, chrono::system_clock::now());
            }catch(...){
                spdlog::error("Could not send data");
            }
            

            strm.close();
        }catch(...){
            spdlog::error("Could not accept connection");
            break;
        }
        
    }
    
}