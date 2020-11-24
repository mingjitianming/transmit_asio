/**
 * @file client.cpp
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief cpp
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "client.h"
#include "asio/yield.hpp"

namespace transmit
{
    Client::Client(const std::string &config, const std::string &user_name)
        : HandleMethod(config),
          socket_(io_context_),
          timer_(io_context_),
          current_method_(std::make_shared<plugins::Transmit>())
    {
    }

    Client::~Client()
    {
    }

    std::shared_ptr<Client> Client::create(const std::string &config, const std::string &user_name)
    {
        //TODO: 修改为共享
        return std::shared_ptr<Client>(new Client(config, user_name));
        // return std::make_shared<Client>(config, user_name);
    }

    void Client::start(const std::string &ip, const int &port)
    {
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(ip), port);
        socket_.async_connect(ep, [this, self = shared_from_this()](const asio::error_code &err) {
            if (!err)
            {
                return step(err);
            }
            else
                stop();
        });
        io_context_.run();
    }

    void Client::step(const asio::error_code &err, size_t bytes)
    {

        reenter(this)
        {
            for (;;)
            {
                if (!started_)
                {
                    started_ = true;
                    std::string a = "5";
                    std::copy(a.begin(), a.end(), write_buffer_);
                    // out << "login " << username_ << "\n";
                }

                yield asio::async_write(socket_, asio::buffer(write_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
                    if (!err)
                    {
                        current_method_->encode(write_buffer_);
                        return step(err, bytes);
                    }
                });

                yield socket_.async_read_some(
                    asio::buffer(read_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
                        if (!err)
                        {
                            return step(err, bytes);
                        }
                    });
                yield io_context_.post([this, self = shared_from_this(), bytes]() {
                    //TODO:

                    // if (read_buffer_.size() > 0)
                    if (strlen(read_buffer_) > 0)
                    {
                        // std::string header(std::begin(read_buffer_), std::begin(read_buffer_) + header_size_);
                        DataHeader header = std::stoi(std::string(std::begin(read_buffer_), std::begin(read_buffer_) + 1));
                        std::cout << "header:" << header << std::endl;
                        current_method_ = getMethod(header);
                        current_method_->parse(read_buffer_, write_buffer_);
                    }

                    return step();
                });
            }
        }
    }

    void Client::stop()
    {
        if (!started_)
            return;
        started_ = false;
        socket_.close();
    }
} // namespace transmit

