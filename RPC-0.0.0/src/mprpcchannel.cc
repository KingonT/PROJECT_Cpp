#include "mprpcchannel.h"
#include "rpcheader.pb.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>              
#include <cerrno>

void MprpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                                google::protobuf::RpcController* controller, 
                                const google::protobuf::Message* request,
                                google::protobuf::Message* response, 
                                google::protobuf::Closure* done)
{
    std::string method_name =  method->name();                                 
    const google::protobuf::ServiceDescriptor * pser =  method->service();
    std::string service_name = pser->name();

    /*  headersize + header + argssize + argsstr    */
    std::string argsstr;
    uint32_t    argssize;
    if(!request->SerializeToString(&argsstr))   
    {
        std::cout <<"SerializetoString failed! :"<< argsstr<<"\n";
    }
    argssize = argsstr.size();
    std::string sendstring;
    
    mprpc::RpcHeader   rpcheader;
    rpcheader.set_service_name(service_name);
    rpcheader.set_method_name(method_name);
    rpcheader.set_argsize(argssize);

    std::string     headerstr;
    uint32_t        headerstrsize;
    if(!rpcheader.SerializePartialToString(&headerstr));                                                           
    {
        std::cout <<"serialize header failed!\n";
        return ;
    }
    headerstrsize = headerstr.size();

    std::string headersize((char*)&headerstrsize ,sizeof(uint32_t));

    sendstring += headersize;
    sendstring += headerstr;
    sendstring += argssize;

    // tcp coding..
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == fd)
    {
        std::cout<<"creator socket failed!:" << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }    

    
} 




