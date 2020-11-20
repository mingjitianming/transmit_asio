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