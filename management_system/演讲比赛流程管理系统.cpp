#include <iostream>

#include"speechManager.h"
using namespace std;
int main() {
    //随机数种子
    srand((unsigned int)time(NULL));
    SpeechManager sm;

//    // 用作测试createSpeakers函数
//    for (auto it = sm.speakers.begin(); it != sm.speakers.end(); it ++){
//        cout << "选手编号：" << it->first
//             << "\t姓名：" << it->second.name
//             << "\t成绩：" << it->second.score[0] << endl;
//    }



    int choice = 0; // 用来存储用户的选项
    while(true){
        sm.showMenu();

        cout << "请输入您的选择： " << endl;
        cin >> choice;
        switch (choice) {
            case 1: // 开始比赛
                sm.startSpeech();
                break;
            case 2: // 查看记录
                sm.showRecord();
                break;            case 3: // 清空记录
                sm.deleteRecord();
                break;
            case 0: // 退出系统
                sm.exitSystem();
            default:
                break;
        }
    }


    return 0;
}
