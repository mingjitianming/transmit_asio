#include "asio.hpp"
#include <utility>

constexpr int BUF_SIZE = 1024;

class Session : public std::enable_shared_from_this<Session>,public asio::coroutine
{
public:
    Session(asio::io_context &io_context);

    void start();

    inline auto &sock() { return socket_; }

    static std::shared_ptr<Session> create(asio::io_context &io_context);

private:
    asio::ip::tcp::socket socket_;
    std::array<char, BUF_SIZE> read_buffer_;
    std::array<char, BUF_SIZE> write_buffer_;
};