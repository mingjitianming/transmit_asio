#ifndef BASE_PLUGIN_H
#define BASE_PLUGIN_H

#include "plugin_factory.h"
#include "type.h"
#include <memory>

template <typename T, typename... Args>
void PLUGIN_EXPORT(T &&cls, Args &&... args)
{
    auto factory = dynamic_cast<PluginFactory *>(getPluginFactory());
    factory->registerClass(std::forward<Args>(args)...,
                           [args...] { return std::static_pointer_cast<Base>(std::make_shared<typename std::remove_reference_t<T>()>(args)...); });
}

class Transmit : public Base
{
public:
    virtual void parse(Buffer &read_buff, Buffer &write_buff) = 0;
    virtual void encode(Buffer &write_buff) = 0;
    virtual ~Transmit() = default;
    template <typename Functor, typename... Args>
    void callbackMethod(Functor &&f, Args &&... args)
    {
        f(std::forward<Args>(args)...);
    }
};



#endif