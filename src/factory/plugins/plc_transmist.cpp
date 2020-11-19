#include "plugins/plc_transmist.h"
#include <iostream>
#include <memory>

PlcTransmit::PlcTransmit(std::string plugin_name)
{
    auto factory = dynamic_cast<PluginFactory *>(getPluginFactory());
    factory->registerClass(plugin_name,
                           [plugin_name] { return std::static_pointer_cast<Base>(std::make_shared<PlcTransmit>(plugin_name)); });
    std::cout << "plctransmit" << std::endl;
}
//  ~PlcTransmis() = default;

void PlcTransmit::parse(Buffer &read_buff, Buffer &write_buff)
{
    std::cout << "enter parse" << std::endl;
    
}
void PlcTransmit::encode(Buffer &write_buff)
{
}

PlcTransmit _PlcTransmit = PlcTransmit("kkk");

// EXPORT_PLUGIN("string", PlcTransmit)
