#include "myhead.h"

//�޸�����
int Bankclient::changepass()
{
	int writecnt = 0;
	char password1[20] = {0};
	char password2[20] = {0};

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
		clientsend.action = CHANGEPWD;
		cout<<"\n�����������룺";
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
		while(strcmp(password1,password2) != 0)
		{
			cout<<"ǰ�����벻һ�£����������룡"<<endl;
			cout<<"\n�����������룺";
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
		}
		strcpy(clientsend.clientpwd,password1);
		Read = 0;
		cout<<"\n���ڴ������Ժ�...."<<endl;
		writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"write error"<<endl;
			return -1;
		}
	}
	return 0;
}