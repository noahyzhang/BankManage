#include "myhead.h"

//≥ı ºªØ socket
Bankclient::Bankclient()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2,2);

	if(WSAStartup(wVersionRequested,&wsaData) != 0)
	{
		return ;
	}
	if(wsaData.wVersion != wVersionRequested)
	{
		WSACleanup();
		return ;
	}

	socketfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(socketfd == INVALID_SOCKET)
	{
		cout<<"create error";
		return ;
	}
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(MYPORT);
	server_addr.sin_addr.s_addr = inet_addr(MYADDR);
	int ret;
	ret = connect(socketfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret == -1)
	{
		cout<<"connect error";
		return ;
	}
	cout<<"connect sucessfully...\n";
	system("cls");
}