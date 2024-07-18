#include "rpcprovider.h"
#include "mprpcapplication.h"
#include  <string>




void RpcProvider::NotifyService(google::protobuf::Service* service)
{

}

void RpcProvider::Run()
{
    std::string ip = mprpcApplication::GetConfig().FindConfig("rpcserviceip");
    uint16_t port = atoi(mprpcApplication::GetConfig().FindConfig("rpcserviceip").c_str());

    muduo::net::InetAddress  address(); 
    
}