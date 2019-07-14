#include "myhead.h"

//销户
int Bankclient::close_account()
{
	int writecnt = 0;
	int i = 0;

	cout<<"请输入要你要销的账户：";
	cin>>clientsend.clientid;
	cout<<"请输入密码：";
	while((clientsend.clientpwd[i]=getch())!=13)  
	{  
		 putch('*');  
		 i++;  
	 }  
	clientsend.clientpwd[i]='\0'; 
	
	clientsend.action = CLOSE_ACCOUNT;
	writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
	if(writecnt == -1)
	{
		cerr<<"write error"<<endl;
		return -1;
	}
	cout<<"\n正在处理，请稍后......"<<endl;
}