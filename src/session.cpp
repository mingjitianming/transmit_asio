#include "session.h"
#include "asio/yield.hpp"

Session::Session(asio::io_context &io_context) : socket_(io_context)
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
std::shared_ptr<Session> Session::create(asio::io_context &io_context)
{
    return std::make_shared<Session>(io_context);
}