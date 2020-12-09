/**
 * @file handle_method.h
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef HANDLE_METHOD_H
#define HANDLE_METHOD_H

#include "base_plugin.h"
#include "type.h"
#include <map>
#include <yaml-cpp/yaml.h>

namespace transmit
{
    class HandleMethod
    {
    public:
        HandleMethod(const std::string &config);
        ~HandleMethod() {}
        auto getMethods() { return msg_id2method_; }
        std::shared_ptr<plugins::Transmit> getMethod(const std::string &plugin_name);
        std::shared_ptr<plugins::Transmit> getMethod(const DataHeader &header);
        DataHeader getHeader(const std::string &name);

    private:
        std::shared_ptr<std::map<std::string, std::shared_ptr<plugins::Transmit>>> methods_;
        std::shared_ptr<std::map<DataHeader, std::shared_ptr<plugins::Transmit>>> msg_id2method_;
    };
} // namespace transmit

#endif