#include "handle_method.h"

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