#include "client.h"
#include "plugins/plc_transmist.h"
#include <memory>

int main()
{
    std::string config = "/home/zmy/project_ws/my_hk_transmit/config/plugins.yaml";
    std::string ip("127.0.0.1");

    std::shared_ptr<transmit::Client> client = transmit::Client::create(config, "zmy");
    std::dynamic_pointer_cast<transmit::plugins::PlcTransmit>(client->getMethod("plc"))
        ->setClientProcess(
            [](int a, int b, cv::Point2f c) {
                std::cout << a + b << std::endl;
            });
    client->start(ip, 8001);
    return 0;
}