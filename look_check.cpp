#include "myhead.h"

//�鿴��ϸ
int Bankclient::look_check()
{
	int writecnt = 0;
	int i = 0;

	cout<<"�����뿨�ţ�";
	cin>>clientsend.clientid;
	cout<<"���������룺";
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
		cout<<"\n���ڴ������Ժ�....."<<endl;
		Read = 0;
		cout<<"\n======================================================================================"<<endl;
		cout<<setw(6)<<"�˺�"<<setw(12)<<"����"<<setw(14)<<"����"<<setw(6)<<"ȡ��"<<setw(6)<<"���"<<endl;
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