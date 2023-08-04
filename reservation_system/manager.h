//
// Created by h r z on 2023/8/1.
//

#ifndef RESERVATION_SYSTEM_MANAGER_H
#define RESERVATION_SYSTEM_MANAGER_H
#include<iostream>
#include"Identity.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"
#include<vector>
using namespace std;

class Manager:public Identity{
public:
    // 默认构造
    Manager();

    // 有参构造 管理员姓名、密码
    Manager(string name, string pwd);

    // 菜单界面
    void openMenu();

    // 添加账号
    void addPerson();

    // 查看账号
    void showPerson();

    // 查看机房信息
    void showComputer();

    // 清空预约记录
    void cleanFile();

    // 初始化容器
    void initVector();

    // 学生容器
    vector<Student> vStu;

    // 教师容器
    vector<Teacher> vTea;

    // 学生、教师重复检测
    bool checkRepeat(int id, int type);

    // 机房容器
    vector<ComputerRoom> vCom;

    // 清理已取消或预约失败的记录
    void cleanOrderFile();
};
#endif //RESERVATION_SYSTEM_MANAGER_H
