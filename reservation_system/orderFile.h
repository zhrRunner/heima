//
// Created by h r z on 2023/8/4.
//

#ifndef RESERVATION_SYSTEM_ORDERFILE_H
#define RESERVATION_SYSTEM_ORDERFILE_H
#include<iostream>
#include<map>
#include"globalFile.h"
#include<fstream>
using namespace std;
class OrderFile{
public:
    // 构造函数
    OrderFile();

    // 更新预约记录
    void updateOrder();

    // 记录的容器 key --- 记录的条数  value --- 具体记录的键值对信息
    map<int, map<string, string>> m_orderData;

    // 预约的记录条数
    int m_Size;

    // 分割order中的字符串
    void splitOrder(string str, char ch, map<string, string> &m);
};
#endif //RESERVATION_SYSTEM_ORDERFILE_H
