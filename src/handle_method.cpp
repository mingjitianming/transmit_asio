/**
 * @file handle_method.cpp
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "handle_method.h"
#include <spdlog/spdlog.h>

HandleMethod::HandleMethod(const std::string &config)
    : methods_(std::make_shared<std::map<std::string, std::shared_ptr<Transmit>>>())
{
    auto factory = dynamic_cast<PluginFactory *>(getPluginFactory());
    const YAML::Node plugins = YAML::LoadFile(config);
    for (auto it = plugins["plugins"].begin(); it != plugins["plugins"].end(); ++it)
    {
        auto name = it->second.as<std::string>();
        std::cout << "methods:" << name << std::endl;
        auto plugin = factory->createInstance<Transmit>(name);
        methods_->emplace(name, std::move(plugin));
    }
}

std::shared_ptr<Transmit> HandleMethod::getMethod(const std::string &plugin_name)
{
    if (methods_->find(plugin_name) != methods_->end())
    {
        return methods_->at(plugin_name);
    }
    else
    {
        spdlog::warn("has no pulin: {} in methods when get method", plugin_name);
        return std::shared_ptr<Transmit>(nullptr);
    }
}