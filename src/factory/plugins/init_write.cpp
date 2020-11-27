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
#include "plugins/init_write.h"
#include "export_macro.h"
#include <iostream>
#include <memory>
namespace transmit
{
    namespace plugins
    {
        InitWrite::InitWrite(std::string plugin_name)
        {
        }
        //  ~PlcTransmis() = default;

        void InitWrite::parse(Buffer &read_buff, Buffer &write_buff)
        {
            if (handle_plc_ != nullptr)
            {
                std::cout << "plc handle function has load" << std::endl;
                handle_plc_(2, 3);
            }
            std::cout << "enter parse" << std::endl;
        }
        void InitWrite::encode(Buffer &write_buff)
        {
        }

        // PLUGIN_EXPORT(InitWrite, "init_write");
    } // namespace plugins
} // namespace transmit
