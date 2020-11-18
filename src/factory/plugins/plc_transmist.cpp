#include "plugins/plc_transmist.h"
// #include "plc_transmist.h"
#include <iostream>
#include <memory>

// factory->registerClass("plugin_name",
//                        [] { return std::static_pointer_cast<Base>(std::make_shared<PlcTransmit>("plugin_name")); });

PlcTransmit::PlcTransmit(std::string plugin_name)
{
    factory->registerClass(plugin_name,
                           [plugin_name] { return std::static_pointer_cast<Base>(std::make_shared<PlcTransmit>(plugin_name)); });
}
//  ~PlcTransmis() = default;

void PlcTransmit::parse()
{
}
void PlcTransmit::encode()
{
}

PlcTransmit trans = PlcTransmit("kkk");

// EXPORT_PLUGIN("string", PlcTransmit)
