#include<iostream>
#include"globalFile.h"
#include"Identity.h"
#include"student.h"
#include "teacher.h"
#include "manager.h"
#include<fstream>
using namespace std;

// 主菜单
void mainMenu(){
    cout << "======================  欢迎来到zhr的机房预约系统  ====================="
         << endl;
    cout << endl << "请输入您的身份" << endl;
    cout << "\t\t---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.学生代表              |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.老    师             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.管 理 员             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.退    出             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t----------------------------------\n";
    cout << "输入您的选择: ";
}

/// 管理员菜单
/// \param manager 管理员指针
void managerMenu(Identity * &manager){
    while(1){
        // 管理员菜单
        manager->openMenu();

        Manager *man = (Manager *)manager;
        int select = 0;
        cin >> select;

        if(select == 1) { //添加账号
            cout << "添加账号-----" << endl;
            man->addPerson();
        } else if (select == 2) { // 查看账号
            cout << "查看账号-----" << endl;
            man->showPerson();
        } else if (select == 3) { // 查看机房
            cout << "查看机房----" << endl;
            man->showComputer();
        } else if (select == 4) { // 清空预约
            man->cleanFile();
        } else if(select == 5) { // 清理预约
            man->cleanOrderFile();
        }
        else if(select == 0){
            cout << "注销成功" << endl;
            mainMenu();
            return ;
        }


    }
}

/// 学生菜单
/// \param student
void studentMenu(Identity* &student){
    while(true){
        student->openMenu();

        Student *stu = (Student *) student;
        int select = 0;
        cin >> select;

        if(select == 1) { // 申请预约
            stu->applyOrder();
        } else if(select == 2) { // 查看自身预约
            stu->showMyOrder();
        } else if(select == 3){ // 查看所有预约
            stu->showAllOrder();
        } else if(select == 4) { // 取消预约
            stu->cancelOrder();
        } else if(select == 0){
            cout << "注销成功！" << endl;
            mainMenu();
            return ;
        }
    }
}

/// 教师菜单
/// \param teacher
void teacherMenu(Identity* &teacher){
    while(true){
        teacher->openMenu();

        Teacher *tea = (Teacher *) teacher;
        int select = 0;
        cin >> select;

        if(select == 1){ // 查看所有预约
            tea->showAllOrder();
        } else if(select == 2) { // 审核预约
            tea->validOrder();
        } else if(select == 0){
            cout << "注销成功！" << endl;
            mainMenu();
            return;
        }
    }
}

/// 登陆功能
/// \param fileName 要操作的文件名
/// \param type 1 ：学生， 2：老师， 3：管理员
void loginIn(string fileName, int type){

    Identity *person = NULL;

    ifstream ifs;
    ifs.open(fileName, ios::in);

    // 文件不存在情况
    if (!ifs.is_open()){
        cout << "文件不存在" << endl;
        ifs.close();
        return ;
    }

    int id = 0;
    string name;
    string pwd;

    if(type == 1) {
        cout << "请输入你的学号：" << endl;
        cin >>id;
    } else if(type == 2) {
        cout << "请输入您的职工编号：" << endl;
        cin >>id;
    }

    cout << "请输入用户名：" << endl;
    cin >> name;

    cout << "请输入密码：" << endl;
    cin >> pwd;

    if (type == 1) {
        // 学生登陆验证
        int fId;
        string fName;
        string fPwd;
        while(ifs >> fId && ifs >> fName && ifs >> fPwd){
            if(id == fId && name == fName && pwd == fPwd){
                cout << "学生登陆验证成功！" << endl;
                person = new Student(id, name, pwd);
                studentMenu(person);
                return ;
            }
        }
    }
    else if(type == 2){
        // 教师登陆验证
        int fId;
        string fName;
        string fPwd;
        while(ifs >> fId && ifs >> fName && ifs >> fPwd){
            if(id == fId && name == fName && pwd == fPwd){
                cout << "教师登陆验证成功！" << endl;
                person = new Teacher(id, name, pwd);
                teacherMenu(person);
                return ;
            }
        }
    }
    else  {
        // 管理员登陆验证
        string fName;
        string fPwd;
        while(ifs >> fName && ifs >> fPwd){
            if(name == fName && pwd == fPwd){
                cout << "管理员登陆验证成功！" << endl;
                person = new Manager(name, pwd);
                managerMenu(person);
                return ;
            }
        }
    }

    cout << "登陆失败！" << endl;
    mainMenu();
    return ;
}



int main() {

    int select  = 0;
    mainMenu();
    while(true){

        cin >> select;
        switch(select){
            case 1 :  // 学生身份
                loginIn(STUDENT_FILE, 1);
                break;
            case 2 :  // 老师身份
                loginIn(TEACHER_FILE, 2);
                break;
            case 3 :  // 管理员身份
                loginIn(ADMIN_FILE, 3);
                break;
            case 0 :  // 退出系统
                cout << "欢迎下一次使用^_^" << endl;
                exit(0);
                break;
            default:
                cout << "输入有误！请重新选择！" << endl;
                mainMenu();
        }
    }


}