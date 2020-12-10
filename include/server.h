/**
 * @file server.h
 * @author zmy (626670628@qq.com)
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
        void start(const bool blocked = true);
        void stop();

    private:
        void doAccept();
        inline void runContextIO(const bool &blocked)
        {
            if (!blocked)
                future_ = std::async(std::launch::async, [this] { io_context_.run(); });
            else
                io_context_.run();
        }

    private:
        asio::io_context io_context_;
        asio::ip::tcp::acceptor acceptor_;
        asio::ip::tcp::endpoint ep_;

        std::future<void> future_;
        std::vector<Session> sessions_;
        // asio::deadline_timer timer_;
    };
} // namespace transmit

#endif