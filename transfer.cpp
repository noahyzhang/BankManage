#include "myhead.h"

//转账
int Bankclient::transfer()
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
		Read = 0;
		cout<<"\n请输入你要转账的卡号：";
		cin>>clientsend.toclientid;
		cout<<"请输入你要转账的金额：";
		cin>>clientsend.captial;
		clientsend.action = TRANSFER;
		cout<<"正在处理，请稍后...."<<endl;
		writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"write error"<<endl;
			return -1;
		}
	}
	return 0;
}