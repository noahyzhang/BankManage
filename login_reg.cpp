#include "myhead.h"

//��½�˵����溯��
int Bankclient::login_menu()
{
	int choice = 0;
	while(1)
	{
		cout<<"\t\t\t\t*===========================================================*"<<endl;
		cout<<"\t\t\t\t|                                                           |"<<endl;
		cout<<"\t\t\t\t|               ��ӭ����ABC���й���ϵͳ                     |"<<endl;
		cout<<"\t\t\t\t|                                                           |"<<endl;
		cout<<"\t\t\t\t|-----------------------------------------------------------|"<<endl;
		cout<<"\t\t\t\t|                     1����½                               |"<<endl;
		cout<<"\t\t\t\t|                     2��ע��                               |"<<endl;
		cout<<"\t\t\t\t|                     0���˳�                               |"<<endl;
		cout<<"\t\t\t\t*-----------------------------------------------------------*"<<endl;
		cout<<"\t\t\t\t������ѡ��";
		cin>>choice;
		if(!(choice == 1||choice == 2||choice == 0))
		{
			cout<<"\t\t\t\t�����������������룺";
			getchar();
			system("cls");
		}
		else
		{
			return choice;
		}
	}
}

//��½�˵�������
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
		cout<<"\t\t\t\t������ְ���ţ�";
		cin>>clientm.userid;
		cout<<"\t\t\t\t���������룺";
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
			cout<<"\n\t\t\t\t������������";
			getchar();
			cin>>clientm.username;
			cout<<"\t\t\t\t���������룺";
			i= 0;
		    while((password1[i]=getch())!=13)  
		    {  
				 putch('*');  
				 i++;  
			 }  
			password1[i]='\0'; 
			cout<<"\n\t\t\t\t��ȷ�����룺";
			i = 0;
			while((password2[i]=getch())!=13)  
		    {  
				 putch('*');  
				 i++;  
			}
			password2[i] = '\0';
			cout<<"\n\t\t\t\t���������е�ַ:";
			cin>>clientm.place_bank;
			if(strcmp(password1,password2) != 0)
			{
				cout<<"\n\t\t\t\tǰ�����벻һ�£�������ע�ᣡ";
				continue;
			}
			else
			{
				cout<<"\n\t\t\t\t����Ϊ������˺ţ�"<<endl;
				Sleep(200);
				srand(time(NULL));
				clientm.userid = rand()%100000+10000;
				strcpy(clientm.password,password1);
				cout<<"\t\t\t\t����ɹ�!"<<endl;
				cout<<"\t\t\t\t�����˺�Ϊ��"<<clientm.userid<<" ,�����Ʊ��ܣ�"<<endl;
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
//��¼ע�ᴦ��
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
					cout<<"\n\t\t\t\t���ڵ�½�����Ժ�....."<<endl;
					Sleep(1000);
					cout<<"��½�ɹ�"<<endl;
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
					cout<<"\n\t\t\t\t�˺Ż�������󣬵�½ʧ�ܣ�"<<endl;
				}
				else if(clientrecv.relay == LOGGED)
				{
					cout<<"\n\t\t\t\t���û��ѵ�¼����½ʧ�ܣ�"<<endl;
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
					cout<<"\t\t\t\tע��ɹ����뷵�ص�½���棡"<<endl;
				}
				else if(clientrecv.relay == REG_FAIL)
				{
					cout<<"\t\t\t\t���û��Ѵ��ڣ�ע��ʧ��!"<<endl;
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
					cout<<"��ӭʹ�ã�лл��"<<endl;
					exit(0);
				}
			}
		}
		getchar();
		getchar();
		system("cls");
	}
}