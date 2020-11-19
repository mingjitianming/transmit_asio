#include "server.h"

int main()
{
    std::string config = "/home/zmy/project_ws/hk_transport/config/plugins.yaml";
    Server ser(8001, config);
    ser.start();
    return 0;
}