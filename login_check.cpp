#include "myhead.h"

//登录
int Thread::login_check()
{
	int result = 0;
	int writecnt = 0;
	char sql[100] = {0};
	MYSQL_RES* mysql_res;
	MYSQL_FIELD* mysql_field;
	MYSQL_ROW mysql_row;
	unsigned int cols;
	int flag = 0;

	sprintf(sql,"select * from staff where userid = %d;",clientrecv.userid);
	result = mysql_query(mysql, sql);
	mysql_res = mysql_store_result(mysql);
	if (result != 0)
	{
		cout<<mysql_error(mysql)<<endl;
		clientrecv.relay = LOG_FAIL;
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
					if(clientrecv.userid == atoi(mysql_row[0])&&strcmp(clientrecv.password,mysql_row[2]) == 0&&atoi(mysql_row[3]) == 0)
					{
						flag = 1;
					}
					if((clientrecv.userid == atoi(mysql_row[0])&&strcmp(clientrecv.password,mysql_row[2]) == 0)&&atoi(mysql_row[3]) == 1)
					{
						flag = 2;
					}
				}
			}
			mysql_free_result(mysql_res);
		}
		if(flag == 1)                                                                               //登陆成功反馈给客户端
		{
			memset(&sql,0,100);
			sprintf(sql,"update staff set loginstate = 1 where userid = %d;",clientrecv.userid);
			result = mysql_query(mysql, sql);
			clientrecv.relay = LOG_SUCCESS;
			writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
			if(writecnt == -1)
			{
				cerr<<"send error!"<<endl;
				return -1;
			}
		}
		else if(flag == 2)                                                                         //用户已登录信息返回给客户端
		{
			clientrecv.relay = LOGGED;
			writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
			if(writecnt == -1)
			{
				cerr<<"send error!"<<endl;
				return -1;
			}
		}
		else                                                                                      //账号密码错误返回给客户端
		{
			clientrecv.relay = LOG_FAIL;
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