#include "myhead.h"

//����
int Bankclient::open_account()
{
	int writecnt = 0;
	char password1[19] = {0};
	char password2[19] = {0};
	int i = 0;
	char ch;
	while(1)
	{
		clientsend.action = OPEN_ACCOUNT;
		cout<<"�������û�������";
		cin>>clientsend.client_name;
		cout<<"���������֤���룺";
		cin>>clientsend.ID_card;
		while(strlen(clientsend.ID_card) != 18)
		{
			memset(&clientsend.ID_card,0,19);
			cout<<"�������֤��ʽ�������������룺";
			cin>>clientsend.ID_card;
		}
		cout<<"���������룺";
		i= 0;
		while((password1[i]=getch())!=13)  
		{  
				putch('*');  
				i++;  
			}  
		password1[i]='\0'; 
		cout<<"\n��ȷ�����룺";
		i = 0;
		while((password2[i]=getch())!=13)  
		{  
				putch('*');  
				i++;  
		}
		password2[i] = '\0';
		if(strcmp(password1,password2) != 0)
		{
			cout<<"\n\t\t\t\tǰ�����벻һ�£�������ע�ᣡ";
			continue;
		}
		else
		{
			strcpy(clientsend.clientpwd,password1);
			break;
		}
	}
	cout<<"\n�Ƿ��ȡ����Y/N��";
	cin>>ch;
	while( !(ch == 'Y'||ch == 'y'||ch == 'N'||ch == 'n'))
	{
		cout<<"�����������������룺"<<endl;
		cin>>ch;
	}
	if(ch == 'Y'||ch == 'y')
	{
		cout<<"����������:";
		cin>>clientsend.captial;
	}
	writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
	if(writecnt == -1)
	{
		cerr<<"write error"<<endl;
		return -1;
	}
	cout<<"���ڴ������Ժ�......"<<endl;
	
	return 0;
}