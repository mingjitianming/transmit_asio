#ifndef SERVER_H
#define SERVER_H

#include "asio.hpp"
#include "session.h"
#include <cstdint>
#include "asio/io_context.hpp"

class Server
{
public:
    Server(std::uint16_t port);
    ~Server() = default;

private:
    void doAccept();

private:
    asio::ip::tcp::acceptor acceptor_;
    asio::io_service io_service_;
    asio::ip::tcp::endpoint ep_;
    // asio::deadline_timer timer_;
};

#endif