/**
 * @file plc_transmist.h
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef PLC_TRANSMIST_H
#define PLC_TRANSMIST_H

#include "base_plugin.h"
#include <functional>
#include <opencv2/opencv.hpp>

namespace transmit
{
    namespace plugins
    {
        class PlcTransmit : public Transmit
        {
        public:
            PlcTransmit() = default;
            PlcTransmit(std::string plugin_name);
            ~PlcTransmit() = default;
            virtual void parse(Buffer &read_buff, Buffer &write_buff) override;
            virtual void encode(Buffer &write_buff) override;
            decltype(auto) setPrecessFunction(auto &&func)
            {
                handle_plc_ = std::forward<decltype(func)>(func);
            }

            decltype(auto) setEncodeFunction(auto &&func)
            {
                handle_write = std::forward<decltype(func)>(func);
            }
            // static std::shared_ptr<PlcTransmit> create(std::string plugin_name)
            // {

            // }

        private:
            std::string name_;
            std::function<void(int, int, cv::Point2f)> handle_plc_ = nullptr;
            std::function<void(int, int)> handle_write = nullptr;
        };
    } // namespace plugins
} // namespace transmit

#endif
