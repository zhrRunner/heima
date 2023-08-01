#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include"speechManager.h"

using namespace std;

// 构造函数
SpeechManager::SpeechManager() {
    // 初始化演讲比赛
    this->initSpeech();

    // 创建选手
    this->createSpeakers();

    // 获取往届记录
    this->loadRecord();
}

// 展示菜单
void SpeechManager:: showMenu() {
    cout << "********************************************" << endl;
    cout << "*************  欢迎参加演讲比赛 ***************" << endl;
    cout << "*************  1.开始演讲比赛  ***************" << endl;
    cout << "*************  2.查看往届记录  ***************" << endl;
    cout << "*************  3.清空比赛记录  ***************" << endl;
    cout << "*************  0.退出比赛程序  ***************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

// 开始演讲比赛 主要控制整个比赛流程
void SpeechManager::startSpeech(){
    // 第一轮比赛
    // 1、抽签
    speechDraw();
    // 2、比赛
    speechContest();
    // 3、显示晋级结果
    scoreShow();

    // 第二轮比赛
    this->count ++;
    // 1、抽签
    speechDraw();
    // 2、比赛
    speechContest();
    // 3、显示最终结果
    scoreShow();
    // 4、保存分数
    saveRecord();

    // 重置比赛
    // 初始化演讲比赛
    this->initSpeech();

    // 创建选手
    this->createSpeakers();

    // 获取往届记录
    this->loadRecord();

}

// 初始化属性
void SpeechManager::initSpeech(){
    // 容器保证为空
    this->v1.clear();
    this->v2.clear();
    this->v3.clear();
    this->speakers.clear();

    // 初始化比赛轮数
    this->count = 1;
    // 初始化记录容器
    this->record.clear();
}

// 创建选手
void SpeechManager::createSpeakers(){
    string nameSeed = "ABCDEFGHIJKL";
    for(int i = 0; i < nameSeed.size(); i ++){
        string name = "选手";
        name += nameSeed[i];
        Speaker sp;
        sp.name = name;
        for(int i = 0; i < 2; i ++) {
            sp.score[i] = 0;
        }

        // 12名选手编号
        int id = 10001 + i;
        this->v1.push_back(id);

        // 编号和选手对应
        this->speakers.insert(make_pair(id, sp));
    }


}

// 抽签
void SpeechManager::speechDraw(){
    cout << "第 << " << this->count << " >>轮比赛正在抽签....." << endl;
    cout << "----------------------" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "抽签后演讲顺序如下：" << endl;

    // 创建随机数引擎
    random_device rd;
    mt19937 gen(rd());

    if(this->count == 1){
        // 第一轮演讲
        shuffle(this->v1.begin(), this->v1.end(), gen);  // 使用随机数引擎和分布函数进行洗牌
        for(auto x : v1){
            cout << x << ' ';
        }
        cout << endl;
    }else{
        // 第二轮演讲
        shuffle(this->v2.begin(), this->v2.end(), gen);
        for(auto x : v2){
            cout << x << ' ';
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
}

// 比赛
void SpeechManager::speechContest(){
    cout << "------------- 第"<< this->count << "轮正式比赛开始：------------- " << endl;
    cout << "第 << " << this->count << " >>轮比赛正在进行....." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    multimap<double, int, greater<double>> mTmp; // 临时的存放分数，选手编号的容器
    vector<int> v;  // 比赛的人员容器
    int num = 0; // 6人为一个小组
    if(this->count == 1) {
        v = this->v1;
    }else {
        v = this->v2;
    }
    // 遍历所有参赛选手
    for(auto x : v){
        num ++;
        deque<double> d; // 评委打分容器
        for (int i = 0; i < 10; i++){
            double score = (rand() % 401 + 600) / 10.0; // 600 ~ 1000
            d.push_back(score);
        }
        sort(d.begin(), d.end(), greater<double>());
        d.pop_back();
        d.pop_front();
        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum / (double)d.size();

        // cout << "编号：" << x << ' ' << this->speakers[x].name << "获取平均分为：" << avg << endl; // 打印分数
        this->speakers[x].score[this->count - 1] = avg;

        // 6个人一组，用临时容器保存
        mTmp.insert(make_pair(avg, x));
        if(num % 6 == 0){ // 一个小组完结
            cout << "第" << num / 6 << "小组比赛名次：" << endl;
            int idx = 1;
            for(auto it = mTmp.begin(); it != mTmp.end(); it ++, idx ++){
                cout << "名次：" << idx
                     << " 编号：" << it->second << " 姓名："
                     << this->speakers[it->second].name
                     << " 成绩：" << this->speakers[it->second].score[this->count - 1]
                     << endl;
            }

            // 取前三名
            int cnt = 0;
            for(auto it = mTmp.begin(); it != mTmp.end() && cnt < 3; it ++, cnt ++){
                if(this->count == 1){
                    this->v2.push_back(it->second);
                }else{
                    this->v3.push_back(it->second);
                }
            }

            mTmp.clear();
            cout << endl;
        }

    }
    cout << "------------- 第" << this->count << "轮比赛完毕  ------------- " << endl;
}

// 显示比赛结果
void SpeechManager::scoreShow(){

    vector<int> v;
    if(this->count == 1){
        v = v2;
        cout << "---------第" << this->count << "轮晋级选手信息如下：-----------" << endl;
    }else{
        v = v3;
        cout << "---------最终优胜者信息如下：-----------" << endl;
    }

    for(auto it = v.begin(); it != v.end(); it ++){
        cout << "选手编号：" << *it
             << " 姓名："<< this->speakers[*it].name
             << " 成绩：" << this->speakers[*it].score[this->count - 1]
             << endl;
    }
    cout << endl;

}

// 保存比赛记录
void SpeechManager::saveRecord(){
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);   // 用输出的方式打开文件  -- 写文件

    // 将每个数据写入文件中
    for(auto it = v3.begin(); it != v3.end(); it ++){
        ofs << *it << ","
            << this->speakers[*it].score[1] << ",";
    }
    ofs << endl;

    ofs.close();

    this->fileIsEmpty = false;
    cout << "记录已经保存!!!" << endl;
    cout << "本届比赛已完毕～期待您的下一次到来～" << endl << endl;
}

// 读取记录
void SpeechManager::loadRecord(){
    ifstream ifs("speech.csv", ios::in);  //输入流对象 读取文件
    if(!ifs.is_open()) {
        this->fileIsEmpty = true;
        cout << "文件不存在！" << endl;
        ifs.close();
        return ;
    }

    char ch;
    ifs >> ch;
    if(ifs.eof()){
        cout << "文件为空！" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    // 文件不为空
    this->fileIsEmpty = false;
    ifs.putback(ch); // 将读取到的单个字符放回去
    string data;
    int index = 0; // 表示第几届
    while(ifs >> data){
        vector<string> v;
        int pos = -1, start = 0;
        while(true){
            pos = data.find(",", start);  // 从0开始查找 ','
            if(pos == -1){
                break;
            }
            string tmp = data.substr(start, pos - start);
            v.push_back(tmp);
            start = pos + 1;
        }
        this->record.insert(make_pair(index, v));
        index ++;
    }
    ifs.close();
}

// 显示往届得分
void SpeechManager::showRecord(){
    if(this->fileIsEmpty){
        cout << "文件不存在，或记录为空！" << endl;
        return;
    }
    for (int i = 0; i < this->record.size(); i ++){
        cout << "第" << i + 1 << "届比赛---->" <<
            "冠军编号" << this->record[i][0] << " 得分：" << this->record[i][1] << " "
            "亚军编号" << this->record[i][2] << " 得分：" << this->record[i][3] << " "
            "季军编号" << this->record[i][4] << " 得分：" << this->record[i][5] << endl;
    }
}

// 删除记录
void SpeechManager::deleteRecord(){
    cout << "确认清空？？？" << endl;
    cout << "1、确认" << endl;
    cout << "2、返回" << endl;
    int select = 0;
    cin >> select;
    if(select == 1){
        //打开模式 ios::trunc 如果存在删除文件并重新创建
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        //初始化属性
        this->initSpeech();

        //创建选手
        this->createSpeakers();


        cout << "清空成功" << endl;
    }
}

// 退出功能
void SpeechManager::exitSystem(){
    cout << "欢迎下次光临～" << endl;
    exit(0);
}

//析构函数
SpeechManager::~SpeechManager() {

}
