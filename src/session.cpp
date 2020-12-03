/**
 * @file session.cpp
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "session.h"
#include "asio/yield.hpp"
#include "message.pb.h"
#include "spdlog/spdlog.h"
#include <functional>
#include <string>

namespace transmit
{
    Session::Session(asio::io_context &io_context, const std::shared_ptr<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>> &methods)
        : socket_(io_context),
          io_context_(io_context),
          methods_(methods),
          read_buffer_("\n"),
          write_buffer_("\n")
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
                yield socket_.async_read_some(
                    asio::buffer(read_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
                        if (!err)
                        {
                            read_buffer_ += "\n";
                            return step(err, bytes);
                        }
                    });
                yield io_context_.post([this, self = shared_from_this(), bytes]() {
                    //TODO:

                    // if (strlen(read_buffer_) > 0)
                    if (read_buffer_.length() > 1)
                    {
                        message::Message msg;
                        msg.ParseFromString(read_buffer_);
                        DataHeader header = msg.msg_id();
                        std::cout << "header:" << header << std::endl;
                        std::cout << msg.src_id() << " " << msg.dest_id() << std::endl;
                        if (header == 0)
                        {
                            std::cout << "header:" << header << std::endl;
                            std::cout << msg.src_id() << " " << msg.dest_id() << std::endl;
                        }
                        std::cout << "header:" << header << std::endl;
                        current_method_ = getMethod(header);
                        current_method_->serverHandle(msg);
                        write_buffer_ = msg.SerializeAsString();
                    }
                    read_buffer_.clear();

                    return step();
                });
                yield asio::async_write(socket_, asio::buffer(write_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
                    if (!err)
                    {
                        // current_method_->encode(write_buffer_);
                        return step(err, bytes);
                    }
                });
            }
        }
    }

    std::shared_ptr<Session> Session::create(asio::io_context &io_context, const std::shared_ptr<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>> &methods)
    {
        //TODO: 添加共享类别
        return std::shared_ptr<Session>(new Session(io_context, methods));
    }

    std::shared_ptr<plugins::Transmit> Session::getMethod(const DataHeader &method_header)
    {

        if (methods_->find(method_header) != methods_->end())
            return methods_->at(method_header);
        else
        {
            std::cerr << "has no parse header:" << method_header << std::endl;
            exit(-1);
        }
    }
} // namespace transmit
