#ifndef __MYHEAD_H_  
#define __MYHEAD_H_  

<<<<<<< HEAD

//使用了socket 网络编程、mysql 数据库（使数据实现了持久化）
//并且使用了创建线程的方式，当客户端连接上来时，我就创建一个线程去处理这个连接
//使用了友元函数，静态成员函数
#include <stdio.h>
=======
>>>>>>> client
#include <winSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
#include <mysql.h>
#include <conio.h> 
#include <time.h>
#include <assert.h>

using namespace std;
#define MYPORT 8888              //socket的端口
#define MYADDR "172.20.10.2"  // socket的IP
#define INTEREST  0.034		//利息，后面没有用
=======
#include <conio.h> 
#include <time.h>
#include <assert.h>
#include <iomanip>

using namespace std;
#define MYPORT 8888
#define MYADDR "172.20.10.2"
#define INTEREST  0.034   //利息，后面没有用
>>>>>>> client

/***************客户端相关指令请求***********/
#define   LOGIN               10                //登陆
#define   REGISTER            11                //注册
#define   EXIT                12                //退出
<<<<<<< HEAD
#define   OPEN_ACCOUNT        13                //开户处理
#define   CLOSE_ACCOUNT       14                //销户处理
#define   EXIT_LOG            15                //退出处理
=======
#define   OPEN_ACCOUNT        13                //开户
#define   CLOSE_ACCOUNT       14                //销户
#define   EXIT_LOG            15                //退出登陆
>>>>>>> client
#define   DEPOSIT             16                //存款处理
#define   WITHDRAWAL          17                //取款处理
#define   MATCHING            18                //匹配账号
#define   CHANGEPWD           19                //修改密码
#define   TRANSFER            20                //转账
#define   LOOK_CHECK          21                //查看账单
#define   LOOK_BALANCE        22                //查看余额

/**************服务器反馈结果****************/
#define   LOG_SUCCESS         23                //登陆成功
#define   LOG_FAIL            24                //登陆失败
#define   REG_SUCCESS         25                //注册成功
#define   REG_FAIL            26                //注册失败
#define   EXIT_OK             27                //退出成功
#define   LOGGED              28                //用户已登陆
#define   OPEN_ACCOUNT_OK     29                //开户成功
#define   OPEN_ACCOUNT_FAIL   30                //开户失败
#define   DEPOSIT_OK          31                //存款成功
#define   DEPOSIT_FAIL        32                //存款失败
#define   CLOSE_ACCOUNT_FAIL  33                //销户成功
#define   CLOSE_ACCOUNT_OK    34                //销户成功
#define   WITHDRAWAL_OK       35                //取款成功
#define   WITHDRAWAL_FAIL     36                //取款失败
#define   CLIENT_SUCCESS      37                //账号密码正确
#define   CLIENT_FAIL         38                //账号密码错误
#define   CHANGEPWD_OK        39                //修改密码成功
#define   CHANGEPWD_FAIL      40                //修改密码失败
#define   TRANSFER_FAIL1      41                //转账失败
#define   TRANSFER_FAIL2      42                //余额不足转账失败
#define   TRANSFER_OK         43                //转账成功
#define   LOOK_CHECK_OK       44                //查询成功
#define   LOOK_CHECK_FAIL     45                //查询失败
#define   LOOK_BALANCE_OK     46                //查询余额成功
#define   LOOK_BALANCE_FAIL   47                //查询余额失败

<<<<<<< HEAD
extern  MYSQL * mysql;                          //数据库句柄
=======
>>>>>>> client

class User{
public:
	int  action;                  //识别操作数
	int  relay;                   //反馈
	int  userid;                  //职工号
	char username[20];            //职工姓名
	char password[20];            //职工密码
	char place_bank[50];          //银行地点
	int  login_state;             //登陆状态
	char ID_card[19];             //身份证
	int  clientid;                //卡号
<<<<<<< HEAD
	int  toclientid;              //转账卡号
	char clientpwd[20];           //密码
	char client_name[20];         //客户姓名
	char toname[20];              //转账用户
	SYSTEMTIME intime;            //存钱时间    //结构体，有年、月、日
=======
	int  toclientid;              //转账的卡号
	char clientpwd[20];           //密码
	char client_name[20];         //客户姓名
	char toname[20];              //转账用户姓名
	SYSTEMTIME intime;            //存钱时间
>>>>>>> client
	SYSTEMTIME outtime;           //取钱时间 
	char  date[30];               //日期
	float captial;                //本金
	float sum_money;              //本息和
	float extra_money;            //利息

public:
	User()
	{
		memset(&action,0,4);
		memset(&relay,0,4);
		memset(&userid,0,4);
		memset(username,0,20);
		memset(password,0,20);
		memset(place_bank,0,20);
		login_state = 0;
		memset(ID_card,0,19);
		memset(clientpwd,0,20);
		memset(client_name,0,20);
		memset(date,0,30);
		captial = 0.0;
		sum_money = 0.0;
		extra_money = 0.0;
	}
};

<<<<<<< HEAD
class Thread:public User
{
public:
	User clientrecv;                                        //接收客户端的信息
	SOCKET clientfd;                                        //客户端套接字
public:
	int register_check();                                   //注册处理
	int login_check();                                      //登陆处理
	int exit_check();                                       //退出处理
	int open_account_check();                               //开户处理
	int close_account_check();                              //销户处理
	int exit_log_check();                                   //退出处理
	int deposit_check();                                    //存款处理
	int withdrawal_check();                                 //取款处理
	int matching_check();                                   //匹配账号处理 
	int changepass_check();                                 //修改密码处理
	int transfer_check();                                   //转账处理
	int look_balance_check();                               //查询余额处理
	int look_check_check();                                 //查询明细
};

class Bankserver:public Thread
{
public:
	SOCKET socketfd;                                        //服务器套接字
	struct sockaddr_in server_addr;                         //服务器地址
public:
	Bankserver();                                           //初始化服务器的相关信息
	~Bankserver();                                          //析构函数
	void connect_client();                                  //连接客户端
	friend DWORD WINAPI read_from_client(LPVOID fd);        //创建线程
};
=======
class Bankclient:public User
{
public:
	SOCKET clientfd;                                        //客户端套接字
	struct sockaddr_in server_addr;                         //服务器地址
    User clientsend;                                        //客户端发送给服务器信息
public:
	Bankclient();                                           //初始化客户端的相关信息
	int login_menu();                                       //登陆界面
	User login_reg();                                       //登陆注册
	int log_reg_check();                                    //登陆注册处理
	int main_menu();                                        //主菜单
	int main_cmd();                                         //执行主菜单
	int exit_log();                                         //退出登陆
	int open_account();                                     //开户
	int close_account();                                    //销户
	int deposit();                                          //存款
	int withdrawal();                                       //取款
	int changepass();                                       //修改密码
	int transfer();                                         //转账
	int look_check();                                       //查询明细
	int look_balance();                                     //查询余额
//	~Bankclient();                                          //析构函数
    static DWORD WINAPI read_from_server(LPVOID fd);        //创建线程
};
extern SOCKET socketfd;
extern User clientrecv;
extern int Read;
>>>>>>> client

#endif