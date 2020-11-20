#include "plugins/plc_transmist.h"
#include "server.h"

int main()
{
    std::string config = "/home/zmy/project_ws/hk_transport/config/plugins.yaml";
    Server ser(8001, config);
    std::dynamic_pointer_cast<PlcTransmit>(ser.getMethod("kkk"))->setPrecessFunction([](int a, int b) {
        std::cout << a + b << std::endl;
    });
    ser.start();
    return 0;
}