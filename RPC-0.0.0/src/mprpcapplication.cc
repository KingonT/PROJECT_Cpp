#include  "mprpcapplication.h"
#include  <stdlib.h>
#include  <unistd.h>
#include  <iostream>

void ShowArgsHelp()
{
        std::cout<<"Uage :\n ./bin  [-i] [config_file] \n";
}


void mprpcApplication::Init(int argc, char** argv)
{
        if(argc < 2)
        {
                ShowArgsHelp();
                exit(EXIT_FAILURE);
        }

        int c = 0;
        std::string  confile;
        while ( c=getopt(argc,argv,"i:")!= -1)
        {
                switch (c)
                {
                case 'i': confile= optarg; break;
                
                case '?': ShowArgsHelp();
                          exit(EXIT_FAILURE);      
                
                case ':': ShowArgsHelp();
                          exit(EXIT_FAILURE);
                default:  ShowArgsHelp();
                          exit(EXIT_FAILURE);
                }
        }
        
        // 加载配置文件

}


mprpcApplication&  mprpcApplication::GetInstance()
{
        static  mprpcApplication app;
        return app;
}