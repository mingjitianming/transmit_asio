# transmit_asio

基于asio库使用c++工厂模式及protobuf3的Any特性实现的功能及消息插件化的通信程序

***todo：目前不清楚asio异步通讯中是否自带线程资源保护，故未在读写处理函数中添加线程锁，若有线程冲突可在异步读写的处理函数中添加线程锁***

## 1. 插件实现

### 1.1 include

```c++
    #include "base_plugin.h"
    #include <functional>
```

### 1.2 需实现函数

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

### 1.3 插件注册

在插件cpp文件中使用如下命令进行注册

```c++ 
PLUGIN_EXPORT(PlcTransmit, "plc");
```

其中PlcTransmit为插件类，"plc"为插件名称。

## 2.消息定义与使用

### 2.1 base_message 定义

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

### 2.2 plugin_message定义

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

### 2.3 plugin_message使用方式

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

## 3.使用插件配置

```yaml
plugins:
  - { name: plc, msg_id: 5 }
  - { name: plc, msg_id: 6 }

```

## 4.插件回调函数设置

```c++
std::dynamic_pointer_cast<transmit::plugins::PlcTransmit>(ser.getMethod("plc"))
    ->setServerProcess(
        [](int a, int b, cv::Point2f c) {
        std::cout << a + b << std::endl;
    });
```

## 5.使用例程见example
