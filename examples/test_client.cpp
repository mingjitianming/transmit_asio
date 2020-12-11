#include "client.h"
#include "plc.pb.h"
#include "plugins/plc_transmist.h"
#include <memory>

int main()
{

    std::string config = "/home/zmy/project_ws/my_hk_transmit/config/plugins.yaml";
    std::string ip("127.0.0.1");

    auto client = transmit::Client::create(config, "plc");
    std::dynamic_pointer_cast<transmit::plugins::PlcTransmit>(client->getMethod("plc"))
        ->setClientProcess(
            [](int a, int b, cv::Point2f c) {
                std::cout << a + b << std::endl;
            });
    client->start(ip, 8001, true);
    message::data::PlcData data;
    data.mutable_request()->set_x(10);
    data.mutable_request()->set_y(2);
    data.mutable_response()->set_x(5);
    data.mutable_response()->set_y(6);
    client->sendMsg(data);
    std::cout << "end node" << std::endl;
    return 0;
}