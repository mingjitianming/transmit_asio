
/**
 * @file base_plugin.h
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef BASE_PLUGIN_H
#define BASE_PLUGIN_H

#include "../type.h"
#include "message.pb.h"
#include "plugin_factory.h"
#include <memory>
#include <type_traits>

namespace transmit
{
    namespace plugins
    {
        // template <typename T, typename... Args>
        // void PLUGIN_EXPORT(T &&cls, Args &&... args)
        // {
        //     auto factory = getPluginFactory<CreateTransmit>();
        //     factory->registerClass(std::forward<Args>(args)...,
        //                            [args...] { return std::static_pointer_cast<Base>(std::make_shared<decltype(typename std::remove_pointer_t<T>())>(args)...); });
        // }

        class Transmit : public Base
        {
        public:
            virtual void clientHandle(message::Message& message) {}
            virtual void serverHandle(message::Message &message) {}
            virtual ~Transmit() = default;
            // decltype(auto) dealWithFunction(const auto &&func);
        };
    } // namespace plugins
} // namespace transmit

#endif