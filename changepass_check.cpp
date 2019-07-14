#include "myhead.h"

//修改密码操作
int Thread::changepass_check()
{
	int writecnt = 0;
	char sql[100] = {0};
	int result = 0;

	sprintf(sql,"update client set password = '%s'where clientid = %d;",clientrecv.clientpwd,clientrecv.clientid);
	result = mysql_query(mysql,sql);
	if(result > 0)                                                                   //修改密码失败
	{
		cout<<mysql_error(mysql)<<endl;
		clientrecv.relay = CHANGEPWD_FAIL;
		writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"send error!"<<endl;
			return -1;
		}
	}
	else
	{
		clientrecv.relay = CHANGEPWD_OK;											 //修改密码成功
		writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"send error!"<<endl;
			return -1;
		}
	}
	return 0;
}