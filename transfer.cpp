#include "myhead.h"

//ת��
int Bankclient::transfer()
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
		Read = 0;
		cout<<"\n��������Ҫת�˵Ŀ��ţ�";
		cin>>clientsend.toclientid;
		cout<<"��������Ҫת�˵Ľ�";
		cin>>clientsend.captial;
		clientsend.action = TRANSFER;
		cout<<"���ڴ������Ժ�...."<<endl;
		writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"write error"<<endl;
			return -1;
		}
	}
	return 0;
}