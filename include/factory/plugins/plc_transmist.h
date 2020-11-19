#ifndef PLC_TRANSMIST_H
#define PLC_TRANSMIST_H

#include "base_plugin.h"
#include <functional>

class PlcTransmit : public Transmit
{
public:
    PlcTransmit() = default;
    PlcTransmit(std::string plugin_name);
    ~PlcTransmit() = default;
    virtual void parse(Buffer &read_buff, Buffer &write_buff) override;
    virtual void encode(Buffer &write_buff) override;

private:
    std::string name_;
    std::function<void()> handle_plc_;
};


#endif
