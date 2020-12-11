/**
 * @file plugin_factory.h
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H
#include "../type.h"
#include "base_plugin_factory.h"
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

namespace transmit
{
    namespace plugins
    {
        template <typename Object>
        class PluginFactory
        {
        public:
            PluginFactory() {}
            virtual ~PluginFactory() = default;

            bool registerClass(const std::string &id,
                               Object constructor)
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

            template <typename T, typename... Args>
            std::shared_ptr<T> createInstance(const std::string &id, Args &&... args)
            {
                auto it = constructors.find(id);
                if (it == constructors.end())
                    return nullptr;
                return std::static_pointer_cast<T>(it->second(std::forward<Args>(args)...));
            }

        protected:
        private:
            PluginFactory(const PluginFactory &) = delete;
            PluginFactory &operator=(const PluginFactory &) = delete;

            // 构造各个类实例的工厂函数
            std::unordered_map<std::string, Object> constructors;
        };

        template <typename Object>
        std::shared_ptr<PluginFactory<Object>> getPluginFactory() //;
        {
            static std::shared_ptr<PluginFactory<Object>> instance = std::make_shared<PluginFactory<Object>>();
            return instance;
        }
    } // namespace plugins
} // namespace transmit
// 插件工厂实例，此处使用std::string作为类标识，便于使用

#endif
