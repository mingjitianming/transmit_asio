# transmit_asio

基于asio库使用c++工厂模式及protobuf3的Any特性实现的功能及消息插件化的通信程序

***todo：目前不清楚asio异步通讯中是否自带线程资源保护，故未在读写处理函数中添加线程锁，若有线程冲突可在异步读写的处理函数中添加线程锁***

## 1. 安装

### 1.1 编译

```shell
git clone https://github.com/mingjitianming/transmit_asio.git
cd transmit_asio
mkdir build && cd build
cmake ..
make
make install
```

### 1.2 CmakeLists中使用

```cmake
# 设置transmit_asio的install路径
set(transmit_DIR "/home/zmy/project_ws/hk_transport/install/share/cmake/transmit")
# 查找package
find_package(transmit)

add_executable(test_server
        ${CMAKE_CURRENT_LIST_DIR}/test_server.cpp
        )
# 使用命名空间链接
target_link_libraries(test_server
                    transmit::server
                    )
```

## 2. 插件实现

### 2.1 include

```c++
    #include "base_plugin.h"
    #include <functional>
```

### 2.2 需实现函数

```c++
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
```

### 2.3 插件注册

在插件cpp文件中使用如下命令进行注册

```c++
PLUGIN_EXPORT(PlcTransmit, "plc");
```

其中PlcTransmit为插件类，"plc"为插件名称。

## 3.消息定义与使用

### 3.1 base_message 定义

```protobuf
message LogInfo
{
    string name = 1;
}

message Message
{
    sfixed32 msg_head = 1;
    sint32 msg_id = 2;
    sint32 src_id = 3;
    sint32 dest_id = 4;
    google.protobuf.Any msg_data = 5;
    sfixed32 msg_tail = 6;
}
```

***todo：由于没有生产测试，该消息定义需根据实际使用进行更改***

### 3.2 plugin_message定义

```protobuf

syntax="proto3";

package message.data;

message PlcData
{
  message Request 
  {
      int32 x = 1;
      int32 y = 2;
  }
  message Response 
  {
      float x = 1;
      float y = 2;
      float theta = 3;
  }
  Request request = 1;
  Response response = 2;
}

```

### 3.3 plugin_message使用方式

```c++
        plugin_message data;
        message::Message msg;
        msg.mutable_msg_data()->PackFrom(data);
```

```c++
        plugin_message data;
        message::Message msg;
        msg.msg_data().UnpackTo(&data);
```

## 4.使用插件配置

```yaml
plugins:
  - { name: plc, msg_id: 5 }
  - { name: plc, msg_id: 6 }

```

## 5.插件回调函数设置

```c++
std::dynamic_pointer_cast<transmit::plugins::PlcTransmit>(ser.getMethod("plc"))
    ->setServerProcess(
        [](int a, int b, cv::Point2f c) {
        std::cout << a + b << std::endl;
    });
```

## 6.使用例程见example
