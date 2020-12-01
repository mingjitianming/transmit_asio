/**
 * @file base_plugin_factory.h
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef BASE_PLUGINFACTORY_H
#define BASE_PLUGINFACTORY_H

#include <memory>

namespace transmit
{
    namespace plugins
    {
        class Base : public std::enable_shared_from_this<Base>
        {
        public:
            virtual ~Base() = default;
        };

    } // namespace plugins
} // namespace transmit

#endif
