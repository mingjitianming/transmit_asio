/**
 * @file plugin_factory.cpp
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "plugin_factory.h"

BasePluginFactory *getPluginFactory()
{
    static PluginFactory instance;
    return &instance;
}