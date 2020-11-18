#include "server.h"

Server::Server(std::uint16_t port)
    : acceptor_(io_context_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    doAccept();
}

void Server::doAccept()
{
    auto session = Session::create(io_context_);
    acceptor_.async_accept(session->sock(),
                           [this, session](std::error_code ec) {
                               if (!ec)
                               {
                                   session->start();
                               }
                               doAccept();
                           });
}