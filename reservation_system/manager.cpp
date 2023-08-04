//
// Created by h r z on 2023/8/1.
//
#include<iostream>
#include"manager.h"
#include<fstream>
#include<algorithm>
#include"globalFile.h"
using namespace std;

// 默认构造
Manager::Manager(){

}

// 有参构造 管理员姓名、密码
Manager::Manager(string name, string pwd) {
    this->m_Name = name;
    this->m_Pwd = pwd;

    // 初始化容器
    this->initVector();


    // 获取机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE,ios::in);
    ComputerRoom c;
    while(ifs >> c.m_ComId && ifs >> c.m_MaxNum){
        vCom.push_back(c);
    }
    cout << "当前机房数量为：" << vCom.size() << endl;
    ifs.close();
}

// 菜单界面
void Manager::openMenu(){
    cout << "欢迎管理员："<<this->m_Name << "登录！" << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.添加账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.查看机房            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.清空预约            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          5.清理预约            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注销登录            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作： " << endl;
}

// 添加账号
void Manager::addPerson(){
    cout << "请输入添加账号的类型：" << endl;
    cout << "1、添加学生" << endl;
    cout << "2、添加教师" << endl;

    int select = 0;
    cin >> select;
    int id;
    string tip, name, pwd, fileName;
    ofstream ofs;

    string errorTip;  // id重复提示

    if(select == 1){
        fileName = STUDENT_FILE;
        tip = "请输入学号：";
        errorTip = "学号重复，请重新输入：";
    }
    else if(select == 2){
        fileName = TEACHER_FILE;
        tip = "请输入职工编号：";
        errorTip = "职工号重复，请重新输入：";
    }

    ofs.open(fileName, ios::out | ios::app);
    cout << tip << endl;

    while(1){
        cin >> id;

        bool ret = this->checkRepeat(id, select);
        if(ret){ // 有重复
            cout << errorTip << endl;
        }
        else break;
    }

    cout << "请输入用户名：" << endl;
    cin >> name;
    cout << "请输入密码：" << endl;
    cin >> pwd;

    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "添加成功！" << endl;
    ofs.close();

    // 初始化容器,这是为了防止 刚加入账号的学生或职工，再次添加时出现重复的情况
    this->initVector();
}

void printStudent(Student &s){
    cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}

void printTeacher(Teacher &t){
    cout << "职工编号：" << t.m_EmpId << " 姓名：" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}

// 查看账号
void Manager::showPerson(){
    cout << "请选择查看内容：" << endl;
    cout << "1、查看所有学生" << endl;
    cout << "2、查看所有老师" << endl;

    int select = 0;
    cin >> select;
    if(select == 1){
        cout << "所有学生信息如下：" << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    } else if(select == 2){
        cout << "所有教师信息如下：" << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
}

// 查看机房信息
void Manager::showComputer(){
    cout << "机房信息如下：" << endl;
    for (auto c : vCom){
        cout << "机房编号：" << c.m_ComId << " 机房最大容量：" << c.m_MaxNum << endl;
    }
}

// 清空预约记录
void Manager::cleanFile(){
    ofstream ofs(ORDER_FILE, ios::trunc); // 表示在打开文件时如果文件已经存在，将清空文件的内容，即截断文件内容为空。如果文件不存在，则会创建一个新文件。
    ofs.close();
    cout << "清空成功！" << endl;
}

// 初始化容器
void Manager::initVector(){
    vStu.clear();
    vTea.clear();

    // 读取学生文件中的信息
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    if(!ifs.is_open()){
        cout << "文件读取失败！" << endl;
        return ;
    }
    Student s;
    while(ifs >> s.m_Id >> s.m_Name >> s.m_Pwd){
        vStu.push_back(s);
    }
    cout << "当前学生数量为：" << vStu.size() << endl;
    ifs.close();

    // 读取教师文件中的信息
    ifs.open(TEACHER_FILE, ios::in);
    if(!ifs.is_open()) {
        cout << "文件读取失败！" << endl;
    }
    Teacher t;
    while(ifs >> t.m_EmpId >> t.m_Name >> t.m_Pwd){
        vTea.push_back(t);
    }
    cout << "当前教师数量为：" << vTea.size() << endl;
    ifs.close();

}

/// 学生、教师重复检测
/// \param id 传入id
/// \param type 传入类型 1:学生 ｜ 2：老师
/// \return true代表有重复， false代表没有重复
bool Manager::checkRepeat(int id, int type){
    if(type == 1){
        for (auto s : vStu){
            if(id == s.m_Id) return true;
        }
    }
    else {
        for (auto t : vTea){
            if(id == t.m_EmpId) return true;
        }
    }
    return false;
}

// 清理已取消或预约失败的记录
void Manager::cleanOrderFile(){
    OrderFile of;
    if(of.m_Size == 0) {
        cout << "暂时没有可清理的预约~" << endl;
        return ;
    }

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0;i < of.m_Size; i++){
        if(of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
            ofs << "date:" << of.m_orderData[i]["date"] << " ";
            ofs << "interval:" << of.m_orderData[i]["interval"] << " ";
            ofs << "stuId:" << of.m_orderData[i]["stuId"] << " ";
            ofs << "stuName:" << of.m_orderData[i]["stuName"] << " ";
            ofs << "roomId:" << of.m_orderData[i]["roomId"] << " ";
            ofs << "status:" << of.m_orderData[i]["status"] << endl;
        }
    }
    ofs.close();
    cout << "已清理所有取消预约和预约不通过的预约记录!" << endl;
}
















