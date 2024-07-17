#pragma once

// 
class mprpcApplication
{
public:
    static void Init(int argc , char** argv);
    static  mprpcApplication& GetInstance();

private:
    mprpcApplication(){};
    mprpcApplication(const mprpcApplication& ) = delete;
    mprpcApplication(mprpcApplication&&) = delete;
};