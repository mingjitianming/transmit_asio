#ifndef BASE_PLUGIN_H
#define BASE_PLUGIN_H

#include "base_plugin_factory.h"
#include "plugin_factory.h"
#include <memory>

// static PluginFactory *factory = dynamic_cast<PluginFactory *>(getPluginFactory());
// PluginFactory *factory = dynamic_cast<PluginFactory *>(getPluginFactory());
static auto factory = std::unique_ptr<PluginFactory>(dynamic_cast<PluginFactory *>(getPluginFactory()));

class Transmit : public Base
{
public:
    virtual void parse() = 0;
    virtual void encode() = 0;
    virtual ~Transmit();
};

// other function class
// struct IMyClassB : public Base
// {
//     virtual void func() const = 0;
// };

#endif