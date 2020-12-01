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
        // asio::streambuf buf_;

        uint header_size_ = 3;
        std::shared_ptr<plugins::Transmit> current_method_;
        std::shared_ptr<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>> methods_;
    };
} // namespace transmit

#endif