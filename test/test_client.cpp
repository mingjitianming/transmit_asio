#include "client.h"
#include "plugins/plc_transmist.h"
#include <memory>

int main()
{
    std::string config = "/home/zmy/project_ws/hk_transport/config/plugins.yaml";
    std::string ip("127.0.0.1");

    std::shared_ptr<Client> client = Client::create(config, "zmy");
    std::dynamic_pointer_cast<PlcTransmit>(client->getMethod("plc"))
        ->setClientProcess(
            [](int a, int b) {
                std::cout << a + b << std::endl;
            });
    client->start(ip, 8001);
    return 0;
}