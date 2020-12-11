/**
 * @file type.h
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef TRANSMIT_TYPE_H
#define TRANSMIT_TYPE_H

#include <array>
#include <functional>
#include <memory>

namespace transmit
{
    namespace plugins
    {
        class Base;
    } // namespace plugins

    constexpr int BUF_SIZE = 1024;
    using Buffer = char[BUF_SIZE];
    using DataHeader = unsigned int;

    using CreateTransmit = std::function<std::shared_ptr<plugins::Base>()>;

} // namespace transmit

#endif