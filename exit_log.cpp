#include "myhead.h"

//ÍË³ö´¦Àí
int Bankclient::exit_log()
{
	int writecnt = 0;

	clientsend.action = EXIT_LOG;
	writecnt = send(socketfd,(char *)&clientsend,sizeof(User),0);
	if(writecnt == -1)
	{
		cerr<<"write error"<<endl;
		return -1;
	}
}