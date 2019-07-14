#include "myhead.h"

//开户
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
		cout<<"请输入用户姓名：";
		cin>>clientsend.client_name;
		cout<<"请输入身份证号码：";
		cin>>clientsend.ID_card;
		while(strlen(clientsend.ID_card) != 18)
		{
			memset(&clientsend.ID_card,0,19);
			cout<<"输入身份证格式错误，请重新输入：";
			cin>>clientsend.ID_card;
		}
		cout<<"请输入密码：";
		i= 0;
		while((password1[i]=getch())!=13)  
		{  
				putch('*');  
				i++;  
			}  
		password1[i]='\0'; 
		cout<<"\n请确认密码：";
		i = 0;
		while((password2[i]=getch())!=13)  
		{  
				putch('*');  
				i++;  
		}
		password2[i] = '\0';
		if(strcmp(password1,password2) != 0)
		{
			cout<<"\n\t\t\t\t前后密码不一致，请重新注册！";
			continue;
		}
		else
		{
			strcpy(clientsend.clientpwd,password1);
			break;
		}
	}
	cout<<"\n是否存取金额：（Y/N）";
	cin>>ch;
	while( !(ch == 'Y'||ch == 'y'||ch == 'N'||ch == 'n'))
	{
		cout<<"输入有误，请重新输入："<<endl;
		cin>>ch;
	}
	if(ch == 'Y'||ch == 'y')
	{
		cout<<"请输入存款金额:";
		cin>>clientsend.captial;
	}
	writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
	if(writecnt == -1)
	{
		cerr<<"write error"<<endl;
		return -1;
	}
	cout<<"正在处理，请稍后......"<<endl;
	
	return 0;
}