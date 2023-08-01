#include<iostream>
#include<vector>
#include<deque>
#include <numeric>
#include<map>

#include"Speaker.h"

using namespace std;

// 设计演讲比赛管理类
class SpeechManager{
public:
    // 构造函数
    SpeechManager() ;

    // 展示菜单
    void showMenu();

    // 退出功能
    void exitSystem();

    // 开始演讲比赛
    void startSpeech();

    // 初始化属性
    void initSpeech();

    // 创建选手
    void createSpeakers();

    // 抽签
    void speechDraw();

    // 比赛
    void speechContest();

    // 显示比赛结果
    void scoreShow();

    // 保存比赛记录
    void saveRecord();

    // 读取记录
    void loadRecord();

    // 显示往届得分
    void showRecord();

    // 删除记录
    void deleteRecord();

    // 文件为空的标志
    bool fileIsEmpty;

    // 往届记录
    map<int, vector<string>> record;

    // 比赛选手编号 容器 12人
    vector<int> v1;

    // 第一轮晋级选手容器 6人
    vector<int> v2;

    // 第二轮胜利者 3人
    vector<int> v3;

    // 存放编号 以及对应的 具体选手的容器
    map<int, Speaker> speakers;

    // 比赛轮数
    int count = 1;

    //析构函数
    ~SpeechManager();
};