#ifndef SESSION_H
#define SESSION_H
#include "asio.hpp"
#include "handle_method.h"
#include "type.h"
#include <map>
#include <utility>

class Session : public std::enable_shared_from_this<Session>, public asio::coroutine
{
public:
    void start();
    void handler(const asio::error_code &err, size_t bytes);
    void step(const asio::error_code &err = asio::error_code(), size_t bytes = 0);

    inline auto &sock() { return socket_; }

    static std::shared_ptr<Session> create(asio::io_context &io_context, const std::shared_ptr<std::map<std::string, std::shared_ptr<Transmit>>> &methods);

private:
    Session(asio::io_context &io_context, const std::shared_ptr<std::map<std::string, std::shared_ptr<Transmit>>> &methods);
    std::shared_ptr<Transmit> getMethod(const std::string &method_header);

private:
    asio::ip::tcp::socket socket_;
    asio::io_context &io_context_;
    // std::array<char, BUF_SIZE> read_buffer_;
    // std::array<char, BUF_SIZE> write_buffer_;
    Buffer read_buffer_;
    Buffer write_buffer_;
    // asio::streambuf buf_;

    uint header_size_ = 3;
    std::shared_ptr<std::map<std::string, std::shared_ptr<Transmit>>> methods_;
};

#endif