//
// Created by hrz on 2023/8/1.
//

#ifndef RESERVATION_SYSTEM_IDENTITY_H
#define RESERVATION_SYSTEM_IDENTITY_H
#include<iostream>
#include<fstream>
#include"globalFile.h"
#include"computerRoom.h"
using namespace std;

// 身份抽象类
class Identity{
public:
    virtual void  openMenu() = 0;

    string m_Name; // 用户名
    string m_Pwd; // 密码
};




#endif //RESERVATION_SYSTEM_IDENTITY_H
