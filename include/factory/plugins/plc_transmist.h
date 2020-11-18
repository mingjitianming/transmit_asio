#ifndef PLC_TRANSMIST_H
#define PLC_TRANSMIST_H

#include "base_plugin.h"
// #include "base_plugin_factory.h"
// #include "plugin_factory.h"
// #include <iostream>
// #include <memory>

class PlcTransmit : public Transmit
{
public:
    PlcTransmit() = default;
    PlcTransmit(std::string plugin_name);
    ~PlcTransmit() = default;
    virtual void parse() override;
    virtual void encode() override;
};

// extern "C"
// {
//     void f(int i)
//     {
//         PlcTransmit trans = PlcTransmit("kkk");
//     }

//     // f(9);
// }

#endif
