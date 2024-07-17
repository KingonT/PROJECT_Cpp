#pragma once
#include "google/protobuf/service.h"

// mprpc
class RpcProvider
{
public:  
    // 框架提供给外部使用的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service* service);

    // 启动rpc服务节点， 开始提供rpc远程调用服务
    void Run();
};