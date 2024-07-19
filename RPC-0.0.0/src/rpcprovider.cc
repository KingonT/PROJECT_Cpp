#include "rpcprovider.h"



void RpcProvider::NotifyService(google::protobuf::Service* service)
{
    ServiceInfo    serinfo;

    // 获取服务对象描述信息
    const google::protobuf::ServiceDescriptor* pserviceDesc = service->GetDescriptor();

    // 获取服务的名字
    std::string sername = pserviceDesc->name();
    // 获取服务对象service的方法数量
    int methodCnt = pserviceDesc->method_count();
    
    std::cout<<"service_name:"<<sername<< "\n";
    std::cout<<"methcount:"<<methodCnt<< "\n";

    for(int i=0; i< methodCnt ; i++)
    {
        // 获取服务对象指定下标的服务方法的描述(抽象描述)
        const google::protobuf::MethodDescriptor* pmethodDesc = pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        serinfo.m_methodmap.insert({method_name, pmethodDesc});
        std::cout<<"method_name:"<<method_name<< "\n";
    }
    serinfo.m_service = service;
    m_servicemap.insert({sername,serinfo});
}

void RpcProvider::Run()
{
    std::string ip = mprpcApplication::GetConfig().FindConfig("rpcserviceip");
    uint16_t port = atoi(mprpcApplication::GetConfig().FindConfig("rpcserviceport").c_str());
    muduo::net::InetAddress  address(ip,port);
    // 创建Tcpserver 对象
    muduo::net::TcpServer  server(&m_eventloop, address , "RpcServiceip");
    //绑定连接回调和消息读写回调方法   分离网络代码和业务代码
    server.setConnectionCallback(std::bind(&RpcProvider::Onconnect,this, std::placeholders::_1));
    server.setMessageCallback(std::bind(&RpcProvider::OnMessage,this,std::placeholders::_1,
                                    std::placeholders::_2,std::placeholders::_3));

    // 设置muduo库的线程
    server.setThreadNum(4);

    server.start();
    m_eventloop.loop();
}

void  RpcProvider::Onconnect(const muduo::net::TcpConnectionPtr& pcon)
{
    if(!pcon->connected())
    {
        pcon->shutdown();
    }
}

void  RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr&,
                            muduo::net::Buffer*,
                            muduo::Timestamp)
{ 
                
}                         