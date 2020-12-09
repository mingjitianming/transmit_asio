/**
 * @file client.h
 * @author zmy (626670628@qq.com)
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
#include "message.pb.h"
#include <future>

#ifndef TRANSMIT_CLIENT_H
#define TRANSMIT_CLIENT_H

namespace transmit
{
    class Client : public std::enable_shared_from_this<Client>, public HandleMethod, public asio::coroutine
    {
    public:
        // Client(const std::string &config, const std::string &user_name);
        ~Client();
        static std::shared_ptr<Client> create(const std::string &config, const std::string &user_name = "");
        void start(const std::string &ip, const int &port, const bool blocked = true);
        void stop();
        void sendMsg(const auto &data);

    private:
        void step(const asio::error_code &err = asio::error_code(), size_t bytes = 0);
        Client(const std::string &config, const std::string &user_name);
        inline bool isRun() { return is_run_; }
        inline void runContextIO(const bool &blocked)
        {
            if (!is_run_)
            {
                is_run_ = true;
                if (!blocked)
                    future_ = std::async(std::launch::async, [self = shared_from_this(), this] { io_context_.run(); });
                else
                    io_context_.run();
            }
        }

    private:
        std::string user_name_;
        bool started_;
        bool is_run_ = false;
        std::future<void> future_;
        std::shared_ptr<plugins::Transmit> current_method_;

        Buffer read_buffer_;
        Buffer write_buffer_;
        asio::io_context io_context_;
        asio::ip::tcp::socket socket_;
        asio::steady_timer timer_;
    };

    void Client::sendMsg(const auto &data)
    {
        message::Message msg;
        msg.set_msg_id(5);
        msg.mutable_msg_data()->PackFrom(data);
        std::string out = msg.SerializeAsString();
        char buffer[1024];
        memset(buffer, '\0', sizeof(buffer));
        std::copy(out.begin(), out.end(), buffer);
        asio::async_write(socket_, asio::buffer(buffer), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
            if (err)
            {
                // spdlog::error("send message failed!");
            }
        });
    }
} // namespace transmit

#endif