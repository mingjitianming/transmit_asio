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
#include <functional>
#include <string>

namespace transmit
{
    Session::Session(asio::io_context &io_context, const std::shared_ptr<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>> &methods)
        : socket_(io_context),
          io_context_(io_context),
          methods_(methods)
    {
        memset(read_buffer_, '\0', sizeof(read_buffer_));
        memset(write_buffer_, '\0', sizeof(write_buffer_));
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
                            if (strlen(read_buffer_) > 0)
                            {

                                message::Message msg;
                                msg.ParseFromString(read_buffer_);
                                DataHeader header = msg.msg_id();
                                std::cout << "header:" << header << std::endl;
                                std::cout << msg.src_id() << " " << msg.dest_id() << std::endl;
                                //XXX:是否要加lock
                                current_method_ = getMethod(header);
                                current_method_->serverHandle(msg);
                                // current_method_.store(getMethod(header));
                                // current_method_.load()->serverHandle(msg);
                                std::string out = msg.SerializeAsString();
                                std::copy(out.begin(), out.end(), write_buffer_);
                            }
                            memset(read_buffer_, '\0', sizeof(read_buffer_));
                            return step(err, bytes);
                        }
                    });

                yield if (strlen(write_buffer_) > 0)
                {
                    asio::async_write(socket_, asio::buffer(write_buffer_), [this, self = shared_from_this()](const asio::error_code &err, size_t bytes) {
                        if (!err)
                        {
                            // current_method_->encode(write_buffer_);
                            memset(write_buffer_, '\0', sizeof(write_buffer_));
                            return step(err, bytes);
                        }
                    });
                }
                else
                {
                    return step();
                }
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
