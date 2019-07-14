#include "myhead.h"

//��ʼ����������
Bankserver::Bankserver()
{
	//����winsocket
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
	//�����׽���
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

	//�󶨵�ַ
	ret = bind(socketfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret == -1)
	{
		cout<<"bind error"<<endl;
		exit(0); 
	}
	cout<<"bind sucessfully...\n";

	//����
	ret = listen(socketfd,10);
	if(ret == -1)
	{
		cout<<"listen error"<<endl;
		exit(0);
	}
	cout<<"listen sucessfully..."<<endl;
}

/**********************���������ӿͻ��˲������߳�***************************/
void Bankserver::connect_client()
{
    int len;
	SOCKET clientfd;  
	struct sockaddr_in client_addr;                         //�ͻ��˵�ַ                            
	DWORD threadId;
	HANDLE handle;
	//���ݿ��ڴ˴���
	my_bool reconnect = true;
	mysql_options(mysql, MYSQL_OPT_RECONNECT, &reconnect);
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	if (!mysql_real_connect(mysql, "localhost", "root", "1234", "bank",0, NULL, 0))
	{
		cout<<"error:"<<mysql_error(mysql)<<endl;
		return ;
	}
	cout<<"connect mysql successfully..."<<endl;
	mysql_query(mysql, "create table staff(userid int primary key,username text,userpass text,loginstate bool,place_bank text);");       //Ա����Ϣ��
	mysql_query(mysql, "create table client(clientid int primary key,clientname text,ID_card text,password text,place_bank text,open_data datetime);");//�ͻ���Ϣ��
	mysql_query(mysql,"create table account(clientid int,deal_time datetime,inaccount float(10,2),outaccount float(10,2),interest float(10,2),balance float(10,2));");   //�ͻ����ױ�
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

/*******************************�̺߳���********************************/
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
			case LOGIN:                                                //��½����
				{
					s.login_check();
					break;
				}
			case REGISTER:
				{
					s.register_check();                                //ע�ᴦ��
					break;
				}
			case EXIT:
				{
					s.exit_check();                                    //�˳�����
					break;
				}
			case EXIT_LOG:                        
				{
					s.exit_log_check();                                //��½֮����˳�����
					break;
				}
			case OPEN_ACCOUNT:                                        
				{
					s.open_account_check();                             //����
					break;
				}
			case CLOSE_ACCOUNT:                                         //����
				{
					s.close_account_check();
					break;
				}
			case MATCHING:                                              //ƥ���˺Ż������Ƿ���ȷ
				{
					s.matching_check();
					break;
				}
			case DEPOSIT:                                               //����
				{
					s.deposit_check();
					break;
				}
			case WITHDRAWAL:                                            //ȡ���
				{
					s.withdrawal_check();
					break;
				}
			case CHANGEPWD:                                             //�޸����봦��
				{
					s.changepass_check();
					break;
				}
			case TRANSFER:                                             //ת�˴���
				{
					s.transfer_check();
					break;
				}
			case LOOK_BALANCE:                                         //��ѯ����
				{
					s.look_balance_check();
					break;
				}
			case LOOK_CHECK:                                           //��ѯ�˵�
				{
					s.look_check_check();
					break;
				}
		}
		memset(&s.clientrecv,0,sizeof(User));
	}
	return 0;
}

/**********************************��������****************************/
Bankserver::~Bankserver()
{
	closesocket(socketfd);
	mysql_close(mysql);
}