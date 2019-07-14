#include "myhead.h"

//销户处理
int Thread::close_account_check()
{
	int writecnt = 0;
	int result = 0;
	int flag = 0;
	char sql[200] = {0};
	MYSQL_RES* mysql_res;
	MYSQL_FIELD* mysql_field;
	MYSQL_ROW mysql_row;
	unsigned int cols;

	sprintf(sql,"select clientid,password from client where clientid = %d;",clientrecv.clientid);
	result = mysql_query(mysql, sql);
	mysql_res = mysql_store_result(mysql);                                                
	if (result != 0)                                                                //查询失败
	{
		cout<<mysql_error(mysql)<<endl;
		clientrecv.relay = CLOSE_ACCOUNT_FAIL;
		writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"send error!"<<endl;
			return -1;
		}
	}
	else
	{
		cols = mysql_num_fields(mysql_res);                                                      
		if (mysql_res)
		{
			while ((mysql_row = mysql_fetch_row(mysql_res)))
			{
				for (unsigned int i=0; i<cols; ++i)
				{
					if(clientrecv.clientid == atoi(mysql_row[0])&&strcmp(clientrecv.clientpwd,mysql_row[1]) == 0)   //判断账户密码是否正确
					{
						flag = 1;
					}
				}
			}
			mysql_free_result(mysql_res);
		}
		if(flag == 0)                                                                                            //账号或密码不正确，销户失败
		{
			clientrecv.relay = CLOSE_ACCOUNT_FAIL;
			writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
			if(writecnt == -1)
			{
				cerr<<"send error!"<<endl;
				return -1;
			}
		}
		else
		{
			sprintf(sql,"delete from client where clientid = %d;",clientrecv.clientid);
			result = mysql_query(mysql, sql);
			sprintf(sql,"delete from account where clientid = %d;",clientrecv.clientid);
			result = mysql_query(mysql, sql);
			clientrecv.relay = CLOSE_ACCOUNT_OK;
			writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
			if(writecnt == -1)
			{
				cerr<<"send error!"<<endl;
				return -1;
			}
		}
	}
	return 0;
}