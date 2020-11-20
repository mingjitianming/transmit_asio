/**
 * @file plc_transmist.cpp
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "plugins/plc_transmist.h"
#include <iostream>
#include <memory>

PlcTransmit::PlcTransmit(std::string plugin_name)
{
    PLUGIN_EXPORT(this, plugin_name);
}
//  ~PlcTransmis() = default;

void PlcTransmit::parse(Buffer &read_buff, Buffer &write_buff)
{
    std::cout << "enter parse" << std::endl;
    if (handle_plc_ != nullptr)
    {
        handle_plc_(2, 3);
    }
}
void PlcTransmit::encode(Buffer &write_buff)
{
}

PlcTransmit _PlcTransmit = PlcTransmit("plc");
