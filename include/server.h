/**
 * @file server.h
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef TRANTSMIT_SERVER_H
#define TRANTSMIT_SERVER_H

#include "asio.hpp"
// #include "asio/io_context.hpp"
#include "handle_method.h"
#include "session.h"
#include <cstdint>

namespace transmit
{
    class Server : public HandleMethod
    {
    public:
        Server(const std::uint16_t &port, const std::string &config = "");
        ~Server() = default;
        void start();
        void stop();

    private:
        void doAccept();

    private:
        asio::io_context io_context_;
        asio::ip::tcp::acceptor acceptor_;
        asio::ip::tcp::endpoint ep_;

        std::vector<Session> sessions_;
        // asio::deadline_timer timer_;
    };
} // namespace transmit

#endif