#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"
#include <iostream>

int main(int argc, char* argv[])
{
    mprpcApplication::Init(argc,argv);
    
    fixbug::UserServices_Stub   stub(new MprpcChannel());
    // stub.CallMethod()
    
    fixbug::LoginRequest  request;
    request.set_name("xiaobideng");
    request.set_pwd(124345);

    fixbug::LoginResponse   response;
    stub.Login(nullptr,&request,&response,nullptr);
    if(!response.success())
    {
        std::cout << response.result().errmsg() << "\n";
        return;
    }
    // here success 


    return 0;
}