#include "timeutils.h"
#include <iostream> 
#include <asio.hpp>
#include <chrono>

using namespace std; 
using namespace asio::ip;

int main() {
    while(true){
        asio::io_context ctx;
        tcp::endpoint ep{tcp::v4(), 1113};
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