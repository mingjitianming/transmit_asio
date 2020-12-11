/**
 * @file plc_transmist.h
 * @author zmy (626670628@qq.com)
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
            virtual void clientHandle(message::Message &message) override;
            virtual void serverHandle(message::Message &message) override;
            decltype(auto) setClientProcess(auto &&func)
            {
                handle_plc_ = std::forward<decltype(func)>(func);
            }

            decltype(auto) setServerProcess(auto &&func)
            {
                server_handle_ = std::forward<decltype(func)>(func);
            }
            // static std::shared_ptr<PlcTransmit> create(std::string plugin_name)
            // {

            // }

        private:
            std::string name_;
            std::function<void(int, int, cv::Point2f)> handle_plc_ = nullptr;
            std::function<void(int, int, cv::Point2f)> server_handle_ = nullptr;
        };
    } // namespace plugins
} // namespace transmit

#endif
