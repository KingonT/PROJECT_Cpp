#include  <iostream>
#include  <string>
#include  "user.pb.h"  
#include  "mprpcapplication.h"
#include  "rpcprovider.h"


class  UserServiceDerived :public fixbug::UserServices
{
public:
    bool  Login(std::string name , std::string pwd)
    {
        std::cout<<"name:"<< name << std::endl;
        std::cout<<"pwd:"<< pwd  << std::endl;
        return true;
    }

    virtual void Login(google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        std::string name = request->name();
        std::string pwd = request->pwd();

        bool login_result =  Login(name,pwd);

        fixbug::ResaultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result); 
        done->Run();
    }

};


int main(int argc ,char* argv[])
{
    mprpcApplication::Init(argc,argv);

    // provdier 是一个rpc网络服务对象。把UserServiceDerived对象发布到rpc节点上
    RpcProvider     provider;
    provider.NotifyService(new UserServiceDerived());
    
    // 启动一个rpc服务发布节点   Run以后进入阻塞状态，远程等待rpc请求
    provider.Run();

    return 0;
}