/**
 * @file client.h
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief 客户端头文件
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "asio.hpp"
#include "asio/steady_timer.hpp"
#include "handle_method.h"

#ifndef TRANSMIT_CLIENT_H
#define TRANSMIT_CLIENT_H

namespace transmit
{
    class Client : public std::enable_shared_from_this<Client>, public HandleMethod, public asio::coroutine
    {
    public:
        Client(const std::string &config, const std::string &user_name);
        ~Client();
        static std::shared_ptr<Client> create(const std::string &config, const std::string &user_name = "");
        void start(const std::string &ip, const int &port);
        void stop();

    private:
        void step(const asio::error_code &err = asio::error_code(), size_t bytes = 0);

    private:
        std::string user_name_;
        bool started_;
        std::shared_ptr<plugins::Transmit> current_method_;

        Buffer read_buffer_;
        Buffer write_buffer_;
        asio::io_context io_context_;
        asio::ip::tcp::socket socket_;
        asio::steady_timer timer_;
    };
} // namespace transmit

#endif