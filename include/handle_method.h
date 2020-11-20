/**
 * @file handle_method.h
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
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
#include <map>
#include <yaml-cpp/yaml.h>

class HandleMethod
{
public:
    HandleMethod(const std::string &config);
    ~HandleMethod() {}
    auto getMethods() { return methods_; }
    std::shared_ptr<Transmit> getMethod(const std::string &plugin_name);

private:
    std::shared_ptr<std::map<std::string, std::shared_ptr<Transmit>>> methods_;
};

#endif