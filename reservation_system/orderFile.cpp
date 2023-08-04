//
// Created by h r z on 2023/8/4.
//
#include"orderFile.h"
using namespace std;

// 构造函数
OrderFile::OrderFile(){
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);

    string date;      //日期
    string interval;  //时间段
    string stuId;     //学生编号
    string stuName;   //学生姓名
    string roomId;    //机房编号
    string status;    //预约状态

    this->m_Size = 0; // 预约记录个数

    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId &&  ifs >> status){
        // 测试代码
/*      cout << date << endl;
        cout << interval << endl;
        cout << stuId << endl;
        cout << stuName << endl;
        cout << roomId << endl;
        cout << status << endl;
*/
//        string key, value;
        map<string, string> m;
        this->splitOrder(date, ':', m);
        this->splitOrder(interval, ':', m);
        this->splitOrder(stuId, ':', m);
        this->splitOrder(stuName, ':', m);
        this->splitOrder(roomId, ':', m);
        this->splitOrder(status, ':', m);

        this->m_orderData.insert(make_pair(this->m_Size, m));
        this->m_Size ++;

//        // 测试代码
//        for(auto order : this->m_orderData) {
//            cout << "第" << order.first << "条预约记录：" << endl;
//            for(auto t : order.second){
//                cout << t.first << ": " << t.second << endl;
//            }
//        }

    }
}

/// 分割order中的字符串
/// \param str 待分割的字符串
/// \param ch 分割字符
/// \param m 字典map
void OrderFile::splitOrder(string str, char ch, map<string, string> &m){
    int pos = str.find(ch);
    if(pos != -1){
        string key = str.substr(0, pos);
        string value = str.substr(pos + 1, str.size() - pos - 1);
        m.insert(make_pair(key, value));
    }
}

// 更新预约记录
void OrderFile::updateOrder(){
    if (this->m_Size == 0){
        return ;
    }

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0;i < m_Size; i++){
        ofs << "date:" << this->m_orderData[i]["date"] << " ";
        ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_orderData[i]["status"] << endl;
    }
    ofs.close();
}