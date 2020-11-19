#include "plugin_factory.h"

BasePluginFactory *getPluginFactory()
{
    static PluginFactory instance;
    return &instance;
}