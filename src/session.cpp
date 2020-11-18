#include "session.h"
#include "asio/yield.hpp"

Session::Session(asio::io_service &io_service) : socket_(io_service)
{
}

void Session::start()
{

    reenter(this)
    {
        for (;;)
        {
            yield int a = 0;
        }
    }
}
std::shared_ptr<Session> Session::create(asio::io_service &io_service)
{
    return std::make_shared<Session>(io_service);
}