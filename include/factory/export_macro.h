/**
 * @file export_macro.h
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PLUGIN_EXPORT_MACRO_H
#define PLUGIN_EXPORT_MACRO_H

#include <string>

#include "plugin_factory.h"
#include "type.h"

#define PLUGIN_EXPORT_INTERNAL(Class, Name, UniqueID)                                                                  \
    namespace                                                                                                          \
    {                                                                                                                  \
        struct ProxyExec##UniqueID                                                                                     \
        {                                                                                                              \
                                                                                                                       \
            using _class = Class;                                                                                      \
            ProxyExec##UniqueID()                                                                                      \
            {                                                                                                          \
                auto factory = getPluginFactory<CreateTransmit>();                                                     \
                factory->registerClass(Name,                                                                           \
                                       [] { return std::static_pointer_cast<Base>(std::make_shared<_class>(Name)); }); \
            }                                                                                                          \
        };                                                                                                             \
        ProxyExec##UniqueID g_register_plugin_##UniqueID;                                                              \
    } // namespace

#define PLUGIN_EXPORT_INTERNAL_HOP1(Class, Name, UniqueID) \
    PLUGIN_EXPORT_INTERNAL(Class, Name, UniqueID)

#define PLUGIN_EXPORT(Class, Name) \
    PLUGIN_EXPORT_INTERNAL_HOP1(Class, Name, __COUNTER__)

#endif // PLUGIN_EXPORT_MACRO_H