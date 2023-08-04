//
// Created by h r z on 2023/8/1.
//
#include<iostream>
#include"teacher.h"
#include "orderFile.h"

using namespace std;

// 默认构造
Teacher::Teacher(){

}

// 有参构造（职工编号、姓名、密码）
Teacher::Teacher(int empId, string name, string pwd) {
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

// 菜单页面
void Teacher::openMenu() {
    cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.查看所有预约          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.审核预约              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.注销登录              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "请选择您的操作： " << endl;
}

// 查看所有预约
void Teacher::showAllOrder() {
    OrderFile of;  // 获取预约信息
    if(of.m_Size == 0){
        cout << "无预约记录" << endl;
        return;
    }
    for (int i = 0; i < of.m_Size; i++){
        cout << i + 1 << "、 ";
        cout << "预约日期：周" << of.m_orderData[i]["date"];
        cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
        cout << " 机房：" << of.m_orderData[i]["roomId"];
        string status = " 状态："; // 0 取消预约  1 审核中  2 已预约  -1 预约失败
        if(of.m_orderData[i]["status"] == "0") status += "预约已取消";
        else if(of.m_orderData[i]["status"] == "1") status += "审核中";
        else if(of.m_orderData[i]["status"] == "2") status += "预约成功";
        else status += "审核未通过，预约失败";
        cout << status << endl;
    }
}

// 审核预约
void Teacher::validOrder() {
    OrderFile of;
    if(of.m_Size == 0) {
        cout << "无预约记录可审核" << endl;
        return;
    }

    vector<int> v; // 存储可审核的记录
    int index = 1;
    for(int i = 0; i < of.m_Size; i++){
        if(of.m_orderData[i]["status"] == "1"){
            v.push_back(i);
            cout << index ++ << "、 ";
            cout << "预约日期：周" << of.m_orderData[i]["date"];
            cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << " 机房：" << of.m_orderData[i]["roomId"];
            string status = " 状态："; // 0 取消预约  1 审核中  2 已预约  -1 预约失败
            status += "审核中";
            cout << status << endl;
        }
    }
    if(v.empty()) {
        cout << "您暂时还没有待审核的预约哦~" << endl;
        return ;
    }

    cout << "请输入审核的预约记录,0代表返回" << endl;
    int select = 0;
    int ret = 0;
    while(true) {
        cin >> select;
        if(select >=0 && select <= v.size()){
            if(select == 0) {
                break;
            }
            else {
                cout << "请输入审核结果：" << endl;
                cout << "1、通过" << endl;
                cout << "2、不通过" << endl;
                while(true){
                    cin >> ret;
                    if(ret == 1) {
                        of.m_orderData[v[select - 1]]["status"] = "2";
                        break;
                    } else if(ret == 2){
                        of.m_orderData[v[select - 1]]["status"] = "-1";
                        break;
                    }
                    cout << "输入有误！请重新输入：";
                }
                of.updateOrder();
                cout << "审核完毕！" << endl;
                break;
            }
        }
        cout << "输入有误！请重新输入：";
    }
}
