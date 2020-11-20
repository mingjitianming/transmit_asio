#include "plugins/plc_transmist.h"
#include <iostream>
#include <memory>

PlcTransmit::PlcTransmit(std::string plugin_name)
{
    PLUGIN_EXPORT(this, "kkk");
    std::cout << "plctransmit" << std::endl;
}
//  ~PlcTransmis() = default;

void PlcTransmit::parse(Buffer &read_buff, Buffer &write_buff)
{
    if (handle_plc_ != nullptr)
    {
        std::cout << "plc handle function has load" << std::endl;
        handle_plc_(2, 3);
    }
    std::cout << "enter parse" << std::endl;
}
void PlcTransmit::encode(Buffer &write_buff)
{
}

PlcTransmit _PlcTransmit = PlcTransmit("kkk");

// EXPORT_PLUGIN("string", PlcTransmit)
