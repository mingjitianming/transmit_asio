/**
 * @file plc_transmist.cpp
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "plugins/plc_transmist.h"
#include "export_macro.h"
#include "plc.pb.h"
#include <iostream>
#include <memory>

namespace transmit
{
    namespace plugins
    {
        PlcTransmit::PlcTransmit(std::string plugin_name) : name_(plugin_name)
        {
        }

        void PlcTransmit::clientHandle(message::Message &message)
        {
            if (message.has_msg_data() && message.msg_data().Is<message::data::PlcData>())
            {
                message::data::PlcData data;
                message.msg_data().UnpackTo(&data);
                std::cout << "enter parse" << std::endl;
                if (handle_plc_ != nullptr)
                {
                    handle_plc_(data.request().x(), data.request().y(), cv::Point2f(1., 2.));
                }
                //TODO:完善
                data.mutable_response()->set_x(1);
                data.mutable_response()->set_y(2);
                data.mutable_response()->set_theta(1);
                message.mutable_msg_data()->PackFrom(data);
            }
            else
            {
                message::data::PlcData data;
                data.mutable_response()->set_x(1);
                data.mutable_response()->set_y(2);
                data.mutable_response()->set_theta(1);
                message.mutable_msg_data()->PackFrom(data);
            }
        }
        void PlcTransmit::serverHandle(message::Message &message)
        {
            if (message.has_msg_data() && message.msg_data().Is<message::data::PlcData>())
            {
                message::data::PlcData data;
                message.msg_data().UnpackTo(&data);
                std::cout << "enter parse" << std::endl;
                if (handle_plc_ != nullptr)
                {
                    handle_plc_(data.request().x(), data.request().y(), cv::Point2f(1., 2.));
                }
                //TODO:完善
                data.mutable_response()->set_x(1);
                data.mutable_response()->set_y(2);
                data.mutable_response()->set_theta(1);
                message.mutable_msg_data()->PackFrom(data);
            }
            else
            {
                message::data::PlcData data;
                data.mutable_request()->set_x(1);
                data.mutable_request()->set_y(2);
                data.mutable_response()->set_x(1);
                data.mutable_response()->set_y(2);
                data.mutable_response()->set_theta(1);
                message.mutable_msg_data()->PackFrom(data);
            }
        }

        PLUGIN_EXPORT(PlcTransmit, "plc");

    } // namespace plugins
} // namespace transmit
