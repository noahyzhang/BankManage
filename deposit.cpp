#include "myhead.h"

//´æ¿î
int Bankclient::deposit()
{
	int writecnt = 0;
	int i = 0;

	cout<<"ÇëÊäÈë¿¨ºÅ£º";
	cin>>clientsend.clientid;
	cout<<"ÇëÊäÈëÃÜÂë£º";
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
		cout<<"\nÇëÊäÈë´æ¿î½ð¶î£º";
		cin>>clientsend.captial;
		Read = 0;
		clientsend.action = DEPOSIT;
		writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"write error"<<endl;
			return -1;
		}
	}
	return 0;
}