#ifndef SERVER_H
#define SERVER_H

#include "asio.hpp"
#include "asio/io_context.hpp"
#include "session.h"
#include <cstdint>

class Server
{
public:
    Server(std::uint16_t port);
    ~Server() = default;

private:
    void doAccept();

private:
    asio::io_context io_context_;
    asio::ip::tcp::acceptor acceptor_;
    asio::ip::tcp::endpoint ep_;
    // asio::deadline_timer timer_;
};

#endif