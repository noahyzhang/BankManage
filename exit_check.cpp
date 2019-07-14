#include  "myhead.h"

//ÍË³ö
int Thread::exit_check()
{
	int writecnt = 0;
	clientrecv.relay = EXIT_OK;
	writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
	if(writecnt == -1)
	{
		cerr<<"send error!"<<endl;
		return -1;
	}
	closesocket(clientfd);
	return 0;
}

//ÍË³öµÇÂ¼
int Thread::exit_log_check()
{
	int writecnt = 0;
	char sql[100] = {0};
	int result = 0;

	clientrecv.relay = EXIT_OK;
	sprintf(sql,"update staff set loginstate = 0 where userid = %d;",clientrecv.userid);
	result = mysql_query(mysql, sql);
	writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
	if(writecnt == -1)
	{
		cerr<<"send error!"<<endl;
		return -1;
	}
	closesocket(clientfd);
	return 0;
}