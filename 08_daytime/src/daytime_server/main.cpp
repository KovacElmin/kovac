#include "timeutils.h"
#include "CLI11.hpp"
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
        asio::io_context ctx;
        tcp::endpoint ep{tcp::v4(), port};
        tcp::acceptor acceptor{ctx, ep};
        acceptor.listen();

        tcp::socket sock{ctx};
        acceptor.accept(sock);
        tcp::iostream strm{std::move(sock)};

        std::time_t t = std::chrono::system_clock::to_time_t(chrono::system_clock::now());
        std::string ts = std::ctime(&t);
        ts.resize(ts.size()-1);


        TIME_UTILS_H::operator<<(strm, chrono::system_clock::now());

        strm.close();
    }
    
}