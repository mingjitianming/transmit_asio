/**
 * @file client.cpp
 * @author zmy (626670628@qq.com)
 * @brief cpp
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "client.h"
#include "asio/yield.hpp"
#include "message.pb.h"
#include <chrono>
#include <spdlog/spdlog.h>

namespace transmit
{
    Client::Client(const std::string &config, const std::string &user_name)
        : HandleMethod(config),
          user_name_(user_name),
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
        socket_.async_connect(ep, [this, self = shared_from_this(), ip, port](const asio::error_code &err) {
            if (!err)
            {
                spdlog::info("connected server:\n \t \t \t \tip:{},  port:{}", ip, port);
                return step(err);
            }
            else
            {
                static auto start_time = std::chrono::steady_clock::now();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if ((std::chrono::steady_clock::now() - start_time) < std::chrono::seconds(10))
                    start(ip, port);
                else
                {
                    spdlog::error("The time of connecting to server is out threshold {}s", 10);
                    stop();
                    exit(-1);
                }
            }
        });

        runContextIO();

    } // namespace transmit

    void Client::step(const asio::error_code &err, size_t bytes)
    {

        reenter(this)
        {
            for (;;)
            {
                if (!started_)
                {
                    started_ = true;
                    message::Message msg;
                    msg.set_msg_id(getHeader(user_name_));
                    msg.set_src_id(10);
                    msg.set_dest_id(20);
                    write_buffer_ = msg.SerializeAsString();
                    std::cout << "write_buffer:" << write_buffer_.size() << " " << write_buffer_.length() << std::endl;
                }

                yield if (!write_buffer_.empty())
                {
                    asio::async_write(socket_, asio::buffer(write_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
                        if (!err)
                        {
                            message::Message msg;
                            msg.ParseFromString(write_buffer_);
                            DataHeader header = msg.msg_id();
                            spdlog::info("message_id:{}", header);
                            write_buffer_.clear();
                            return step(err, bytes);
                        }
                        else
                        {
                            spdlog::error("errrrrrrrrrrrrrr");
                        }
                    });
                }
                else
                {
                    return step();
                }
                

                // yield std::cout << "write buffer_:" << write_buffer_.size() << std::endl;
                yield socket_.async_read_some(
                    asio::buffer(read_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
                        if (!err)
                        {
                            if (read_buffer_.length() > 0)
                            {
                                message::Message msg;
                                msg.ParseFromString(read_buffer_);
                                DataHeader header = msg.msg_id();
                                std::cout << "header:" << header << std::endl;
                                current_method_ = getMethod(header);
                                current_method_->clientHandle(msg);
                                write_buffer_ = msg.SerializeAsString();
                            }
                            read_buffer_.clear();
                            return step(err, bytes);
                        }
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

    void Client::sendMsg(const auto &data)
    {
        message::Message msg;
        // msg.set_msg_id(getHeader(user_name_));
        msg.mutable_msg_data()->PackFrom(&data);
        std::string out = msg.SerializeAsString();
        std::copy(out.begin(), out.end(), write_buffer_);
        std::string hell = "hello";
        asio::async_write(socket_, asio::buffer(hell), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
            if (err)
            {
                spdlog::error("send message failed!");
            }
        });
    }
} // namespace transmit
