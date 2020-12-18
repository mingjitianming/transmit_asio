# transmit_asio

基于asio库使用c++工厂模式及protobuf3的Any特性实现的功能及消息插件化的通信程序

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

## 2.消息定义

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

## 3.使用插件配置

```yaml
plugins:
  - { name: plc, msg_id: 5 }
  - { name: plc, msg_id: 6 }

```
