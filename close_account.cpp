#include "myhead.h"

//����
int Bankclient::close_account()
{
	int writecnt = 0;
	int i = 0;

	cout<<"������Ҫ��Ҫ�����˻���";
	cin>>clientsend.clientid;
	cout<<"���������룺";
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
	cout<<"\n���ڴ������Ժ�......"<<endl;
}