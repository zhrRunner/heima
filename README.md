# heima

### management_system of ITheima C++

### 1.1 比赛规则

* 学校举行一场演讲比赛，共有**12个人**参加。**比赛共两轮**，第一轮为淘汰赛，第二轮为决赛。
* 比赛方式：**分组比赛，每组6个人**；选手每次要随机分组，进行比赛
* 每名选手都有对应的**编号**，如 10001 ~ 10012 
* 第一轮分为两个小组，每组6个人。 整体按照选手编号进行**抽签**后顺序演讲。
* 当小组演讲完后，淘汰组内排名最后的三个选手，**前三名晋级**，进入下一轮的比赛。
* 第二轮为决赛，**前三名胜出**
* 每轮比赛过后需要**显示晋级选手的信息**

### 1.2 程序功能

* 开始演讲比赛：完成整届比赛的流程，每个比赛阶段需要给用户一个提示，用户按任意键后继续下一个阶段
* 查看往届记录：查看之前比赛前三名结果，每次比赛都会记录到文件中，文件用.csv后缀名保存
* 清空比赛记录：将文件中数据清空
* 退出比赛程序：可以退出当前程序

-----

### reservation_system of ITheima C++

### 2.1 身份简介

分别有三种身份使用该程序

* **学生代表**：申请使用机房
* **教师**：审核学生的预约申请
* **管理员**：给学生、教师创建账号

### 2.2 机房简介

机房总共有3间

* 1号机房   --- 最大容量20人
* 2号机房   --- 最多容量50人
* 3号机房   --- 最多容量100人

### 2.3申请简介

* 申请的订单每周由管理员负责清空。
* 学生可以预约未来一周内的机房使用，预约的日期为周一至周五，预约时需要选择预约时段（上午、下午）
* 教师来审核预约，依据实际情况审核预约通过或者不通过

### 2.4 系统具体需求

* 首先进入登录界面，可选登录身份有：
    * 学生代表
    * 老师
    * 管理员
    * 退出
* 每个身份都需要进行验证后，进入子菜单
    * 学生需要输入 ：学号、姓名、登录密码
    * 老师需要输入：职工号、姓名、登录密码
    * 管理员需要输入：管理员姓名、登录密码
* 学生具体功能
    * 申请预约    ---   预约机房
    * 查看自身的预约    ---  查看自己的预约状态
    * 查看所有预约   ---   查看全部预约信息以及预约状态
    * 取消预约    ---   取消自身的预约，预约成功或审核中的预约均可取消
    * 注销登录    ---   退出登录
* 教师具体功能
    * 查看所有预约   ---   查看全部预约信息以及预约状态
    * 审核预约    ---   对学生的预约进行审核
    * 注销登录    ---   退出登录
* 管理员具体功能
    * 添加账号    ---   添加学生或教师的账号，需要检测学生编号或教师职工号是否重复
    * 查看账号    ---   可以选择查看学生或教师的全部信息
    * 查看机房    ---   查看所有机房的信息
    * 清空预约    ---   清空所有预约记录
    * 清理预约    ---   清理已经取消的预约和预约失败的预约记录
    * 注销登录    ---   退出登录

