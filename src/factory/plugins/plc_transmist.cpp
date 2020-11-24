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

namespace transmit
{
    namespace plugins
    {
        PlcTransmit::PlcTransmit(std::string plugin_name) : name_(plugin_name)
        {
            PLUGIN_EXPORT(this, plugin_name);
        }

        void PlcTransmit::parse(Buffer &read_buff, Buffer &write_buff)
        {
            std::cout << "enter parse" << std::endl;
            if (handle_plc_ != nullptr)
            {
                handle_plc_(2, 3, cv::Point2f(1., 2.));
            }
            std::string a = "568";
            std::copy(a.begin(), a.end(), write_buff);
        }
        void PlcTransmit::encode(Buffer &write_buff)
        {
        }
        PlcTransmit _PlcTransmit = PlcTransmit("plc");
    } // namespace plugins
} // namespace transmit
