/**
 * @file server.cpp
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "server.h"
#include <spdlog/spdlog.h>

Server::Server(const std::uint16_t &port, const std::string &config)
    : acceptor_(io_context_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
      HandleMethod(config)
{
    // setup logger
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] %^[%L] %v%$");
}

void Server::doAccept()
{
    auto session = Session::create(io_context_, getMethods());
    acceptor_.async_accept(session->sock(),
                           [this, session](std::error_code ec) {
                               if (!ec)
                               {
                                   session->start();
                               }
                               doAccept();
                           });
}

void Server::start()
{
    doAccept();
    io_context_.run();
}