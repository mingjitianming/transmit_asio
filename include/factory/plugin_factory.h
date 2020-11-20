/**
 * @file plugin_factory.h
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H
#include "base_plugin_factory.h"
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

// 插件工厂实例，此处使用std::string作为类标识，便于使用
class PluginFactory : public BasePluginFactory
{
public:
    PluginFactory() {}
    virtual ~PluginFactory() = default;

    bool registerClass(const std::string &id,
                       std::function<std::shared_ptr<Base>()> constructor)
    {
        if (constructors.find(id) != constructors.end())
            return false;
        constructors[id] = constructor;
    }

    void unregisterClass(const std::string &id)
    {
        auto it = constructors.find(id);
        if (it != constructors.end())
            constructors.erase(it);
    }

protected:
    virtual std::shared_ptr<Base> createInstanceWithBase(const std::string &id)
    {
        auto it = constructors.find(id);
        if (it == constructors.end())
            return nullptr;
        return it->second();
    }

private:
    PluginFactory(const PluginFactory &) = delete;
    PluginFactory &operator=(const PluginFactory &) = delete;

    // 构造各个类实例的工厂函数
    std::unordered_map<std::string, std::function<std::shared_ptr<Base>()>> constructors;
};

// extern "C" BasePluginFactory *getPluginFactory()
// {
//     static PluginFactory instance;
//     return &instance;
// }

// BasePluginFactory *getPluginFactory()
// {
//     static PluginFactory instance;
//     return &instance;
// }

#endif
