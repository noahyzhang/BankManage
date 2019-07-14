#include "myhead.h"

//登陆菜单界面函数
int Bankclient::login_menu()
{
	int choice = 0;
	while(1)
	{
		cout<<"\t\t\t\t*===========================================================*"<<endl;
		cout<<"\t\t\t\t|                                                           |"<<endl;
		cout<<"\t\t\t\t|               欢迎来到ABC银行管理系统                     |"<<endl;
		cout<<"\t\t\t\t|                                                           |"<<endl;
		cout<<"\t\t\t\t|-----------------------------------------------------------|"<<endl;
		cout<<"\t\t\t\t|                     1、登陆                               |"<<endl;
		cout<<"\t\t\t\t|                     2、注册                               |"<<endl;
		cout<<"\t\t\t\t|                     0、退出                               |"<<endl;
		cout<<"\t\t\t\t*-----------------------------------------------------------*"<<endl;
		cout<<"\t\t\t\t请输入选择：";
		cin>>choice;
		if(!(choice == 1||choice == 2||choice == 0))
		{
			cout<<"\t\t\t\t输入有误，请重新输入：";
			getchar();
			system("cls");
		}
		else
		{
			return choice;
		}
	}
}

//登陆菜单处理函数
User Bankclient::login_reg()
{
	int choice = 0;
	char password1[20] = {0};
	char password2[20] = {0};
	int i = 0;
	User clientm; 
	choice = login_menu();
	memset(&clientm,0,sizeof(User));
	if(choice == 1)
	{
		clientm.action = LOGIN;
		cout<<"\t\t\t\t请输入职工号：";
		cin>>clientm.userid;
		cout<<"\t\t\t\t请输入密码：";
		 while((clientm.password[i]=getch())!=13)  
		 {  
			 putch('*');  
			 i++;  
		 }  
		clientm.password[i]='\0';  
		return clientm;
	}
	else if(choice == 2)
	{
		while(1)
		{
			memset(&clientm,0,sizeof(User));
			clientm.action = REGISTER;
			cout<<"\n\t\t\t\t请输入姓名：";
			getchar();
			cin>>clientm.username;
			cout<<"\t\t\t\t请输入密码：";
			i= 0;
		    while((password1[i]=getch())!=13)  
		    {  
				 putch('*');  
				 i++;  
			 }  
			password1[i]='\0'; 
			cout<<"\n\t\t\t\t请确认密码：";
			i = 0;
			while((password2[i]=getch())!=13)  
		    {  
				 putch('*');  
				 i++;  
			}
			password2[i] = '\0';
			cout<<"\n\t\t\t\t请输入银行地址:";
			cin>>clientm.place_bank;
			if(strcmp(password1,password2) != 0)
			{
				cout<<"\n\t\t\t\t前后密码不一致，请重新注册！";
				continue;
			}
			else
			{
				cout<<"\n\t\t\t\t正在为你分配账号！"<<endl;
				Sleep(200);
				srand(time(NULL));
				clientm.userid = rand()%100000+10000;
				strcpy(clientm.password,password1);
				cout<<"\t\t\t\t分配成功!"<<endl;
				cout<<"\t\t\t\t您的账号为："<<clientm.userid<<" ,请妥善保管！"<<endl;
				return clientm;
			}
		}
	}
	else
	{
		clientm.action = EXIT;
		return clientm;
	}
}
//登录注册处理
int Bankclient::log_reg_check()
{
	int writecnt = 0;
	int recvcnt = 0;
	DWORD threadId;
	HANDLE handle;
	while(1)
	{
		memset(&clientsend,0,sizeof(User));
		clientsend = login_reg();
		switch(clientsend.action)
		{
			case LOGIN:
			{
				writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
				if(writecnt == -1)
				{
					cerr<<"write error"<<endl;
					return -1;
				}
				recvcnt = recv(socketfd,(char*)&clientrecv,sizeof(User),0);
				if(recvcnt == -1)
				{
					cerr<<"read error"<<endl;
					return -1;
				}
				if(clientrecv.relay == LOG_SUCCESS)
				{
					cout<<"\n\t\t\t\t正在登陆，请稍后....."<<endl;
					Sleep(1000);
					cout<<"登陆成功"<<endl;
					system("cls");
					handle = CreateThread(NULL,0,read_from_server,(LPVOID)clientfd,0,&threadId);
					if(handle == NULL)
					{
						cout<<"create error"<<GetLastError()<<endl;
						exit(-1);
					}
					main_cmd();
				}
				else if(clientrecv.relay == LOG_FAIL)
				{
					cout<<"\n\t\t\t\t账号或密码错误，登陆失败！"<<endl;
				}
				else if(clientrecv.relay == LOGGED)
				{
					cout<<"\n\t\t\t\t该用户已登录，登陆失败！"<<endl;
				}
				break;
			}
			case REGISTER:
			{
				writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
				if(writecnt == -1)
				{
					cerr<<"write error"<<endl;
					return -1;
				}
				recvcnt = recv(socketfd,(char *)&clientrecv,sizeof(User),0);
				if(recvcnt == -1)
				{
					cerr<<"read error"<<endl;
					return -1;
				}
				if(clientrecv.relay == REG_SUCCESS)
				{
					cout<<"\t\t\t\t注册成功，请返回登陆界面！"<<endl;
				}
				else if(clientrecv.relay == REG_FAIL)
				{
					cout<<"\t\t\t\t该用户已存在，注册失败!"<<endl;
				}
				break;
			}
			case EXIT:
			{
				writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
				if(writecnt == -1)
				{
					cerr<<"write error"<<endl;
					return -1;
				}
				recvcnt = recv(socketfd,(char *)&clientrecv,sizeof(User),0);
				if(recvcnt == -1)
				{
					cerr<<"read error"<<endl;
					return -1;
				}
				if(clientrecv.relay == EXIT_OK)
				{
					cout<<"欢迎使用，谢谢！"<<endl;
					exit(0);
				}
			}
		}
		getchar();
		getchar();
		system("cls");
	}
}