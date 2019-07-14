#include "myhead.h"

//×¢²áÓÃ»§
int Thread::register_check()
{
	int result = 0;
	int writecnt = 0;
	char sql[100] = {0};

	sprintf(sql,"insert into staff values(%d,'%s','%s',%d,'%s');",clientrecv.userid,clientrecv.username,clientrecv.password,clientrecv.login_state,clientrecv.place_bank);
	result = mysql_query(mysql, sql);
	cout<<"result = "<<result<<endl;
	if (result != 0)
	{
		cout<<mysql_error(mysql)<<endl;
		clientrecv.relay = REG_FAIL;
		writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"send error!"<<endl;
			return -1;
		}
	}
	else
	{
		clientrecv.relay = REG_SUCCESS;
		writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"send error!"<<endl;
			return -1;
		}
	}
	return 0;
}