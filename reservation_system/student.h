//
// Created by h r z on 2023/8/1.
//

#ifndef RESERVATION_SYSTEM_STUDENT_H
#define RESERVATION_SYSTEM_STUDENT_H
#include<iostream>
#include"Identity.h"
#include "computerRoom.h"
#include<vector>
#include"orderFile.h"
using namespace std;

class Student : public Identity{
public:
    // 默认构造
    Student();

    // 有参构造(学号、姓名、密码)
    Student(int id, string name, string pwd);

    // 菜单页面
    void openMenu();

    // 申请预约
    void applyOrder();

    // 查看我的预约
    void showMyOrder();

    // 查看所有预约
    void showAllOrder();

    // 取消预约
    void cancelOrder();

    // 学生学号
    int m_Id;

    // 机房容器
    vector<ComputerRoom> vCom;

};


#endif //RESERVATION_SYSTEM_STUDENT_H
