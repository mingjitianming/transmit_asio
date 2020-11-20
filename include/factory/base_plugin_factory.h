/**
 * @file base_plugin_factory.h
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
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

class Base : public std::enable_shared_from_this<Base>
{
public:
    virtual ~Base() = default;
};

// 插件工厂接口
struct BasePluginFactory
{
    virtual ~BasePluginFactory() = default;

    template <typename T>
    std::shared_ptr<T> createInstance(const std::string id)
    {
        return std::static_pointer_cast<T>(createInstanceWithBase(id));
    }

protected:
    virtual std::shared_ptr<Base> createInstanceWithBase(const std::string &id) = 0;
};

// 整个dll，只需要导出这唯一一个符号，其他所有类都不需要导出
// extern "C" BasePluginFactory *getPluginFactory();
BasePluginFactory *getPluginFactory();

#endif
