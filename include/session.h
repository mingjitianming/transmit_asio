/**
 * @file session.h
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef SESSION_H
#define SESSION_H
#include "asio.hpp"
#include "handle_method.h"
#include "type.h"
// #include <atomic>
#include <map>
#include <utility>

namespace transmit
{
    class Session : public std::enable_shared_from_this<Session>, public asio::coroutine
    {
    public:
        void start();
        void handler(const asio::error_code &err, size_t bytes);

        inline auto &sock() { return socket_; }
        void sendMsg(const auto &data);
        static std::shared_ptr<Session> create(asio::io_context &io_context, const std::shared_ptr<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>> &methods);

    private:
        Session(asio::io_context &io_context, const std::shared_ptr<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>> &methods);
        std::shared_ptr<plugins::Transmit> getMethod(const DataHeader &method_header);
        void step(const asio::error_code &err = asio::error_code(), size_t bytes = 0);

    private:
        asio::ip::tcp::socket socket_;
        asio::io_context &io_context_;
        Buffer read_buffer_;
        Buffer write_buffer_;

        // std::atomic<std::shared_ptr<plugins::Transmit>> current_method_;
        std::shared_ptr<plugins::Transmit> current_method_;
        std::shared_ptr<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>> methods_;
    };

    void Session::sendMsg(const auto &data)
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