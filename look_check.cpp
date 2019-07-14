#include "myhead.h"

//查看明细
int Bankclient::look_check()
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
		cout<<"\n正在处理，请稍后....."<<endl;
		Read = 0;
		cout<<"\n======================================================================================"<<endl;
		cout<<setw(6)<<"账号"<<setw(12)<<"日期"<<setw(14)<<"存入"<<setw(6)<<"取出"<<setw(6)<<"余额"<<endl;
		clientsend.action = LOOK_CHECK;
		writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"write error"<<endl;
			return -1;
		}
	}
	return 0;
}