#include "myhead.h"

//取款
int Bankclient::withdrawal()
{
	int writecnt = 0;
	int i = 0;

	cout<<"请输入卡号：";
	cin>>clientsend.clientid;
	cout<<"请输入密码：";
	while((clientsend.clientpwd[i]=getch())!=13)  
	{  
		 putch('*');  
		 i++;  
	 }  
	clientsend.clientpwd[i]='\0';
	clientsend.action = MATCHING;
	writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
	if(writecnt == -1)
	{
		cerr<<"write error"<<endl;
		return -1;
	}
	Sleep(1000);
	if(Read == 1)
	{
		cout<<"\n请输入取款金额：";
		cin>>clientsend.captial;
		Read = 0;
		clientsend.action = WITHDRAWAL;
		writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"write error"<<endl;
			return -1;
		}
	}
	return 0;
}