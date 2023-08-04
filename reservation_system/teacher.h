//
// Created by h r z on 2023/8/1.
//

#ifndef RESERVATION_SYSTEM_TEACHER_H
#define RESERVATION_SYSTEM_TEACHER_H
#include<iostream>
#include"Identity.h"
using namespace std;
class Teacher : public Identity{
public:
    // 默认构造
    Teacher();

    // 有参构造（职工编号、姓名、密码）
    Teacher(int empId, string name, string pwd);

    // 菜单页面
    void openMenu();

    // 查看所有预约
    void showAllOrder();

    // 审核预约
    void validOrder();

    int m_EmpId;  // 教师编号
};

#endif //RESERVATION_SYSTEM_TEACHER_H
