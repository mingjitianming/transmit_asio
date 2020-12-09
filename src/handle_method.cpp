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
        : methods_(std::make_shared<std::map<std::string, std::shared_ptr<plugins::Transmit>>>()),
          msg_id2method_(std::make_shared<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>>())
    {
        auto factory = plugins::getPluginFactory<CreateTransmit>();
        const YAML::Node plugins = YAML::LoadFile(config)["plugins"];
        for (const auto &it : plugins)
        {
            auto name = it["name"].as<std::string>();
            spdlog::info("load method:{}", name);
            auto header = it["msg_id"].as<DataHeader>();
            std::cout << name << ":" << header << std::endl;
            if (methods_->find(name) == methods_->end())
            {
                auto plugin = factory->createInstance<plugins::Transmit>(name);
                if (plugin == nullptr)
                {
                    spdlog::error("has no plugin: {}", name);
                    exit(-1);
                }
                methods_->emplace(name, plugin);
                msg_id2method_->emplace(header, plugin);
            }
            else if (msg_id2method_->find(header) == msg_id2method_->end())
            {
                auto it = methods_->find(name);
                msg_id2method_->emplace(header, it->second);
            }
            else
            {
                spdlog::error("plugin config is woring");
                exit(-1);
            }
        }
    }

    std::shared_ptr<plugins::Transmit> HandleMethod::getMethod(const std::string &plugin_name)
    {
        if (methods_->find(plugin_name) != methods_->end())
        {
            return methods_->at(plugin_name);
        }
        else
        {
            spdlog::error("has no pulin: {} in methods when get method", plugin_name);
            return std::shared_ptr<plugins::Transmit>(nullptr);
        }
    }

    std::shared_ptr<plugins::Transmit> HandleMethod::getMethod(const DataHeader &header)
    {
        if (msg_id2method_->find(header) != msg_id2method_->end())
        {
            return msg_id2method_->at(header);
        }
        else
        {
            spdlog::error("has no header: {} in methods when get method", header);
            return std::shared_ptr<plugins::Transmit>(nullptr);
        }
    }

    DataHeader HandleMethod::getHeader(const std::string &name)
    {
        // if (name2header_.find(name) != name2header_.end())
        // {
        //     return name2header_[name];
        // }
        // else
        // {
        //     spdlog::error("has no header: {} in methods when get plugin name", name);
        //     exit(-1);
        // }
    }
} // namespace transmit
