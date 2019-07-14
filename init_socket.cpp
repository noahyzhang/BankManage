#include "myhead.h"

//初始化网络链接
Bankserver::Bankserver()
{
	//启动winsocket
	WORD wVersionRequested;                             
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2,2);

	if(WSAStartup(wVersionRequested,&wsaData) != 0)
	{
		return ;
	}
	if(wsaData.wVersion != wVersionRequested)
	{
		WSACleanup();
		return ;
	}
	//创建套接字
	socketfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(socketfd == INVALID_SOCKET)
	{
		cout<<"create error";
		return ;
	}
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(MYPORT);
	server_addr.sin_addr.s_addr = inet_addr(MYADDR);
	int opt = 1;
	int ret;
	ret = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	if (ret == SOCKET_ERROR)
	{
		cout<<"error with code = "<<WSAGetLastError()<<endl;
		exit(1);
	}
	cout<<"socket successfully..."<<endl;

	//绑定地址
	ret = bind(socketfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret == -1)
	{
		cout<<"bind error"<<endl;
		exit(0); 
	}
	cout<<"bind sucessfully...\n";

	//监听
	ret = listen(socketfd,10);
	if(ret == -1)
	{
		cout<<"listen error"<<endl;
		exit(0);
	}
	cout<<"listen sucessfully..."<<endl;
}

/**********************服务器连接客户端并创建线程***************************/
void Bankserver::connect_client()
{
    int len;
	SOCKET clientfd;  
	struct sockaddr_in client_addr;                         //客户端地址                            
	DWORD threadId;
	HANDLE handle;
	//数据库在此创建
	my_bool reconnect = true;
	mysql_options(mysql, MYSQL_OPT_RECONNECT, &reconnect);
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	if (!mysql_real_connect(mysql, "localhost", "root", "1234", "bank",0, NULL, 0))
	{
		cout<<"error:"<<mysql_error(mysql)<<endl;
		return ;
	}
	cout<<"connect mysql successfully..."<<endl;
	mysql_query(mysql, "create table staff(userid int primary key,username text,userpass text,loginstate bool,place_bank text);");       //员工信息表
	mysql_query(mysql, "create table client(clientid int primary key,clientname text,ID_card text,password text,place_bank text,open_data datetime);");//客户信息表
	mysql_query(mysql,"create table account(clientid int,deal_time datetime,inaccount float(10,2),outaccount float(10,2),interest float(10,2),balance float(10,2));");   //客户交易表
	while(1)
	{
		len = sizeof(server_addr);
		clientfd = accept(socketfd,(struct sockaddr *)&client_addr,&len);
		if(clientfd == INVALID_SOCKET)
		{
			cout<<"accept error"<<endl;
			return ;
		}
		cout<<"accept sucessully...\n";
		cout<<inet_ntoa(client_addr.sin_addr)<<" "<<ntohs(client_addr.sin_port)<<endl;
		handle = CreateThread(NULL,0,read_from_client,(LPVOID)clientfd,0,&threadId);
		if(handle == NULL)
		{
			cout<<"create error"<<GetLastError()<<endl;
			exit(-1);
		}
	}
}

/*******************************线程函数********************************/
DWORD WINAPI read_from_client(LPVOID fd)
{
	Thread s;
	s.clientfd = (SOCKET)fd;
	int recvcnt;
	while(1)
	{
		recvcnt = recv(s.clientfd,(char *)&s.clientrecv,sizeof(User),0);
		if(recvcnt == SOCKET_ERROR)
		{
			cerr<<"read error"<<endl;
			break;
		}
		if(recvcnt == 0)
		{
			cout<<"client close"<<endl;
			break;
		}
		switch(s.clientrecv.action)
		{
			case LOGIN:                                                //登陆处理
				{
					s.login_check();
					break;
				}
			case REGISTER:
				{
					s.register_check();                                //注册处理
					break;
				}
			case EXIT:
				{
					s.exit_check();                                    //退出处理
					break;
				}
			case EXIT_LOG:                        
				{
					s.exit_log_check();                                //登陆之后的退出处理
					break;
				}
			case OPEN_ACCOUNT:                                        
				{
					s.open_account_check();                             //开户
					break;
				}
			case CLOSE_ACCOUNT:                                         //销户
				{
					s.close_account_check();
					break;
				}
			case MATCHING:                                              //匹配账号或密码是否正确
				{
					s.matching_check();
					break;
				}
			case DEPOSIT:                                               //存款处理
				{
					s.deposit_check();
					break;
				}
			case WITHDRAWAL:                                            //取款处理
				{
					s.withdrawal_check();
					break;
				}
			case CHANGEPWD:                                             //修改密码处理
				{
					s.changepass_check();
					break;
				}
			case TRANSFER:                                             //转账处理
				{
					s.transfer_check();
					break;
				}
			case LOOK_BALANCE:                                         //查询余额处理
				{
					s.look_balance_check();
					break;
				}
			case LOOK_CHECK:                                           //查询账单
				{
					s.look_check_check();
					break;
				}
		}
		memset(&s.clientrecv,0,sizeof(User));
	}
	return 0;
}

/**********************************析构函数****************************/
Bankserver::~Bankserver()
{
	closesocket(socketfd);
	mysql_close(mysql);
}