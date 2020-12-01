/**
 * @file handle_method.cpp
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "handle_method.h"
#include <spdlog/spdlog.h>

namespace transmit
{
    HandleMethod::HandleMethod(const std::string &config)
        : methods_(std::make_shared<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>>())
    {
        auto factory = plugins::getPluginFactory<CreateTransmit>();
        const YAML::Node plugins = YAML::LoadFile(config);
        for (auto it = plugins["plugins"].begin(); it != plugins["plugins"].end(); ++it)
        {
            auto name = it->first.as<std::string>();
            spdlog::info("load method:{}", name);
            auto header = it->second.as<DataHeader>();
            auto plugin = factory->createInstance<plugins::Transmit>(name);
            if (plugin == nullptr)
            {
                spdlog::error("has no plugin: {}", name);
                exit(-1);
            }
            methods_->emplace(header, std::move(plugin));
            name2header_.emplace(name, header);
        }
        if (methods_->size() != name2header_.size())
            spdlog::error("plugin config is woring");
    }

    std::shared_ptr<plugins::Transmit> HandleMethod::getMethod(const std::string &plugin_name)
    {
        if (name2header_.find(plugin_name) != name2header_.end())
        {
            return methods_->at(name2header_[plugin_name]);
        }
        else
        {
            spdlog::error("has no pulin: {} in methods when get method", plugin_name);
            return std::shared_ptr<plugins::Transmit>(nullptr);
        }
    }

    std::shared_ptr<plugins::Transmit> HandleMethod::getMethod(const DataHeader &header)
    {
        if (methods_->find(header) != methods_->end())
        {
            return methods_->at(header);
        }
        else
        {
            spdlog::error("has no header: {} in methods when get method", header);
            return std::shared_ptr<plugins::Transmit>(nullptr);
        }
    }

    DataHeader HandleMethod::getHeader(const std::string &name)
    {
        if (name2header_.find(name) != name2header_.end())
        {
            return name2header_[name];
        }
        else
        {
            spdlog::error("has no header: {} in methods when get plugin name", name);
            exit(-1);
        }
    }
} // namespace transmit
