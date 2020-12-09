/**
 * @file test_server.cpp
 * @author zmy (626670628@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "plugins/plc_transmist.h"
#include "server.h"
#include <opencv2/opencv.hpp>

int main()
{
    std::string config = "/home/zmy/project_ws/my_hk_transmit/config/plugins.yaml";
    transmit::Server ser(8001, config);
    std::dynamic_pointer_cast<transmit::plugins::PlcTransmit>(ser.getMethod("plc"))
    ->setServerProcess(
        [](int a, int b, cv::Point2f c) {
        std::cout << a + b << std::endl;
    });
    ser.start();
    return 0;
}