#include "myhead.h"

//开户处理
int Thread::open_account_check()
{
	int result = 0;
	int writecnt = 0;
	char sql[200] = {0};
	MYSQL_RES* mysql_res;
	MYSQL_FIELD* mysql_field;
	MYSQL_ROW mysql_row;
	unsigned int cols;
	int flag = 0;

	sprintf(sql,"select * from staff where userid = %d;",clientrecv.userid);
	result = mysql_query(mysql, sql);
	mysql_res = mysql_store_result(mysql);                                                //找出银行开户的地点存入开户数据库中
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
					strcpy(clientrecv.place_bank,mysql_row[4]);
				}
			}
			mysql_free_result(mysql_res);
		}
	}
	srand(time(NULL));
	clientrecv.clientid = rand()%1000000+100000;
	GetSystemTime(&clientrecv.intime);
	sprintf(sql,"insert into client values(%d,'%s','%s','%s','%s','%d-%d-%d %d:%d:%d')",clientrecv.clientid,clientrecv.client_name,clientrecv.ID_card,clientrecv.clientpwd,clientrecv.place_bank,clientrecv.intime.wYear,clientrecv.intime.wMonth,clientrecv.intime.wDay,clientrecv.intime.wHour,clientrecv.intime.wMinute,clientrecv.intime.wSecond);
	result = mysql_query(mysql, sql);
	if(result > 0)                                                                            //开户失败！
	{
		cout<<mysql_error(mysql)<<endl;
		clientrecv.relay = OPEN_ACCOUNT_FAIL;
		writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"send error!"<<endl;
			return -1;
		}
		return -1;
	}
	else
	{
		if(clientrecv.captial > 0)
		{
			clientrecv.sum_money = clientrecv.captial;
			sprintf(sql,"insert into account(clientid ,deal_time,inaccount,balance) values(%d,'%d-%d-%d %d:%d:%d',%.2f,%.2f);",clientrecv.clientid,clientrecv.intime.wYear,clientrecv.intime.wMonth,clientrecv.intime.wDay,clientrecv.intime.wHour,clientrecv.intime.wMinute,clientrecv.intime.wSecond,clientrecv.captial,clientrecv.sum_money);
			result = mysql_query(mysql,sql);
			cout<<result<<endl;
			if(result > 0)                                                                   //存款失败
			{
				cout<<mysql_error(mysql)<<endl;
				clientrecv.relay = DEPOSIT_FAIL;
				writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
				if(writecnt == -1)
				{
					cerr<<"send error!"<<endl;
					return -1;
				}
			}                                                                               //存款成功/开户成功
			clientrecv.relay = OPEN_ACCOUNT_OK;
			writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
			if(writecnt == -1)
			{
				cerr<<"send error!"<<endl;
				return -1;
			}		
		}
		else
		{
			clientrecv.relay = OPEN_ACCOUNT_OK;                                            //开户成功
			writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
			if(writecnt == -1)
			{
				cerr<<"send error!"<<endl;
				return -1;
			}
			return -1;
		}
	}
	return 0;
}