#include "session.h"
#include "asio/yield.hpp"
#include <assert.h>
#include <functional>

Session::Session(asio::io_context &io_context, const std::shared_ptr<std::map<std::string, std::shared_ptr<Transmit>>> &methods)
    : socket_(io_context),
      io_context_(io_context),
      methods_(methods)
{
}

void Session::start()
{
    step();
}

void Session::handler(const asio::error_code &err, size_t bytes)
{
    int h = 0;
}

void Session::step(const asio::error_code &err, size_t bytes)
{

    reenter(this)
    {
        for (;;)
        {
            // yield asio::async_read_some(
            //     socket_, asio::buffer(read_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
            //         if (!err)
            //         {
            //             std::cout << "length:" << bytes << std::endl;
            //             return step(err, bytes);
            //         }
            //     });
            yield socket_.async_read_some(
                asio::buffer(read_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
                    if (!err)
                    {
                        return step(err, bytes);
                    }
                });
            yield io_context_.post([this, self = shared_from_this(), bytes]() {
                //TODO:

                if (read_buffer_.size() > 0)
                {
                    std::string header(std::begin(read_buffer_), std::begin(read_buffer_) + header_size_);
                    std::cout << "header:" << header << std::endl;
                    auto parse = getMethod(header);
                    parse->parse(read_buffer_, write_buffer_);
                }

                return step();
            });
            yield asio::async_write(socket_, asio::buffer(write_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
                if (!err)
                    return step(err, bytes);
            });
        }
    }
}

std::shared_ptr<Session> Session::create(asio::io_context &io_context, const std::shared_ptr<std::map<std::string, std::shared_ptr<Transmit>>> &methods)
{
    return std::shared_ptr<Session>(new Session(io_context, methods));
}

std::shared_ptr<Transmit> Session::getMethod(const std::string &method_header)
{

    if (methods_->find(method_header) != methods_->end())
        return methods_->at(method_header);
    else
    {
        std::cerr << "has no parse header:" << method_header << std::endl;
        exit(-1);
    }
}