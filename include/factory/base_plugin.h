
/**
 * @file base_plugin.h
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
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
#include "plugin_factory.h"
#include <memory>
#include <type_traits>

namespace transmit
{
    namespace plugins
    {
        template <typename T, typename... Args>
        void PLUGIN_EXPORT(T &&cls, Args &&... args)
        {
            auto factory = dynamic_cast<PluginFactory *>(getPluginFactory());
            factory->registerClass(std::forward<Args>(args)...,
                                   [args...] { return std::static_pointer_cast<Base>(std::make_shared<decltype(typename std::remove_pointer_t<T>())>(args)...); });
        }

        class Transmit : public Base
        {
        public:
            virtual void parse(Buffer &read_buff, Buffer &write_buff) {}
            virtual void encode(Buffer &write_buff) {}
            virtual ~Transmit() = default;
            // decltype(auto) dealWithFunction(const auto &&func);
        };
    } // namespace plugins
} // namespace transmit

#endif