#ifndef __MYHEAD_H_  
#define __MYHEAD_H_  

<<<<<<< HEAD

//ʹ����socket �����̡�mysql ���ݿ⣨ʹ����ʵ���˳־û���
//����ʹ���˴����̵߳ķ�ʽ�����ͻ�����������ʱ���Ҿʹ���һ���߳�ȥ�����������
//ʹ������Ԫ��������̬��Ա����
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
#define MYPORT 8888              //socket�Ķ˿�
#define MYADDR "172.20.10.2"  // socket��IP
#define INTEREST  0.034		//��Ϣ������û����
=======
#include <conio.h> 
#include <time.h>
#include <assert.h>
#include <iomanip>

using namespace std;
#define MYPORT 8888
#define MYADDR "172.20.10.2"
#define INTEREST  0.034   //��Ϣ������û����
>>>>>>> client

/***************�ͻ������ָ������***********/
#define   LOGIN               10                //��½
#define   REGISTER            11                //ע��
#define   EXIT                12                //�˳�
<<<<<<< HEAD
#define   OPEN_ACCOUNT        13                //��������
#define   CLOSE_ACCOUNT       14                //��������
#define   EXIT_LOG            15                //�˳�����
=======
#define   OPEN_ACCOUNT        13                //����
#define   CLOSE_ACCOUNT       14                //����
#define   EXIT_LOG            15                //�˳���½
>>>>>>> client
#define   DEPOSIT             16                //����
#define   WITHDRAWAL          17                //ȡ���
#define   MATCHING            18                //ƥ���˺�
#define   CHANGEPWD           19                //�޸�����
#define   TRANSFER            20                //ת��
#define   LOOK_CHECK          21                //�鿴�˵�
#define   LOOK_BALANCE        22                //�鿴���

/**************�������������****************/
#define   LOG_SUCCESS         23                //��½�ɹ�
#define   LOG_FAIL            24                //��½ʧ��
#define   REG_SUCCESS         25                //ע��ɹ�
#define   REG_FAIL            26                //ע��ʧ��
#define   EXIT_OK             27                //�˳��ɹ�
#define   LOGGED              28                //�û��ѵ�½
#define   OPEN_ACCOUNT_OK     29                //�����ɹ�
#define   OPEN_ACCOUNT_FAIL   30                //����ʧ��
#define   DEPOSIT_OK          31                //���ɹ�
#define   DEPOSIT_FAIL        32                //���ʧ��
#define   CLOSE_ACCOUNT_FAIL  33                //�����ɹ�
#define   CLOSE_ACCOUNT_OK    34                //�����ɹ�
#define   WITHDRAWAL_OK       35                //ȡ��ɹ�
#define   WITHDRAWAL_FAIL     36                //ȡ��ʧ��
#define   CLIENT_SUCCESS      37                //�˺�������ȷ
#define   CLIENT_FAIL         38                //�˺��������
#define   CHANGEPWD_OK        39                //�޸�����ɹ�
#define   CHANGEPWD_FAIL      40                //�޸�����ʧ��
#define   TRANSFER_FAIL1      41                //ת��ʧ��
#define   TRANSFER_FAIL2      42                //����ת��ʧ��
#define   TRANSFER_OK         43                //ת�˳ɹ�
#define   LOOK_CHECK_OK       44                //��ѯ�ɹ�
#define   LOOK_CHECK_FAIL     45                //��ѯʧ��
#define   LOOK_BALANCE_OK     46                //��ѯ���ɹ�
#define   LOOK_BALANCE_FAIL   47                //��ѯ���ʧ��

<<<<<<< HEAD
extern  MYSQL * mysql;                          //���ݿ���
=======
>>>>>>> client

class User{
public:
	int  action;                  //ʶ�������
	int  relay;                   //����
	int  userid;                  //ְ����
	char username[20];            //ְ������
	char password[20];            //ְ������
	char place_bank[50];          //���еص�
	int  login_state;             //��½״̬
	char ID_card[19];             //���֤
	int  clientid;                //����
<<<<<<< HEAD
	int  toclientid;              //ת�˿���
	char clientpwd[20];           //����
	char client_name[20];         //�ͻ�����
	char toname[20];              //ת���û�
	SYSTEMTIME intime;            //��Ǯʱ��    //�ṹ�壬���ꡢ�¡���
=======
	int  toclientid;              //ת�˵Ŀ���
	char clientpwd[20];           //����
	char client_name[20];         //�ͻ�����
	char toname[20];              //ת���û�����
	SYSTEMTIME intime;            //��Ǯʱ��
>>>>>>> client
	SYSTEMTIME outtime;           //ȡǮʱ�� 
	char  date[30];               //����
	float captial;                //����
	float sum_money;              //��Ϣ��
	float extra_money;            //��Ϣ

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
	User clientrecv;                                        //���տͻ��˵���Ϣ
	SOCKET clientfd;                                        //�ͻ����׽���
public:
	int register_check();                                   //ע�ᴦ��
	int login_check();                                      //��½����
	int exit_check();                                       //�˳�����
	int open_account_check();                               //��������
	int close_account_check();                              //��������
	int exit_log_check();                                   //�˳�����
	int deposit_check();                                    //����
	int withdrawal_check();                                 //ȡ���
	int matching_check();                                   //ƥ���˺Ŵ��� 
	int changepass_check();                                 //�޸����봦��
	int transfer_check();                                   //ת�˴���
	int look_balance_check();                               //��ѯ����
	int look_check_check();                                 //��ѯ��ϸ
};

class Bankserver:public Thread
{
public:
	SOCKET socketfd;                                        //�������׽���
	struct sockaddr_in server_addr;                         //��������ַ
public:
	Bankserver();                                           //��ʼ���������������Ϣ
	~Bankserver();                                          //��������
	void connect_client();                                  //���ӿͻ���
	friend DWORD WINAPI read_from_client(LPVOID fd);        //�����߳�
};
=======
class Bankclient:public User
{
public:
	SOCKET clientfd;                                        //�ͻ����׽���
	struct sockaddr_in server_addr;                         //��������ַ
    User clientsend;                                        //�ͻ��˷��͸���������Ϣ
public:
	Bankclient();                                           //��ʼ���ͻ��˵������Ϣ
	int login_menu();                                       //��½����
	User login_reg();                                       //��½ע��
	int log_reg_check();                                    //��½ע�ᴦ��
	int main_menu();                                        //���˵�
	int main_cmd();                                         //ִ�����˵�
	int exit_log();                                         //�˳���½
	int open_account();                                     //����
	int close_account();                                    //����
	int deposit();                                          //���
	int withdrawal();                                       //ȡ��
	int changepass();                                       //�޸�����
	int transfer();                                         //ת��
	int look_check();                                       //��ѯ��ϸ
	int look_balance();                                     //��ѯ���
//	~Bankclient();                                          //��������
    static DWORD WINAPI read_from_server(LPVOID fd);        //�����߳�
};
extern SOCKET socketfd;
extern User clientrecv;
extern int Read;
>>>>>>> client

#endif