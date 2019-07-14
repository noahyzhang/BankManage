#include "myhead.h"

//转账处理
int Thread::transfer_check()
{
	int writecnt = 0;
	char sql[200] = {0};
	int result = 0;
	float account = 0;                      //存放长刺余额
	float account1 = 0;
	char date[100] = {0};                   //暂时存放上一次的日期

	MYSQL_RES* mysql_res;
	MYSQL_FIELD* mysql_field;
	MYSQL_ROW mysql_row;
	unsigned int cols;
	int flag = 0;

	sprintf(sql,"select clientid,clientname from client where clientid = %d;",clientrecv.toclientid);   //查找所转账的账号是否存在
	result = mysql_query(mysql,sql);
	mysql_res = mysql_store_result(mysql); 
	if(result > 0)
	{
		cout<<mysql_error(mysql)<<endl;
		clientrecv.relay = TRANSFER_FAIL1;
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
					if(clientrecv.toclientid == atoi(mysql_row[0]))
					{
						strcpy(clientrecv.toname,mysql_row[1]);
						flag = 1;
					}
				}
			}
			mysql_free_result(mysql_res);
		}
		if(flag == 0)
		{
			clientrecv.relay = TRANSFER_FAIL1;
			writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
			if(writecnt == -1)
			{
				cerr<<"send error!"<<endl;
				return -1;
			}
		}
		else
		{
			sprintf(sql,"select clientid,deal_time,interest,balance from account where clientid = %d;",clientrecv.toclientid);
			result = mysql_query(mysql,sql);
			mysql_res = mysql_store_result(mysql); 
			if(result != 0)
			{
				cout<<mysql_error(mysql)<<endl;
				cout<<"查询失败！"<<endl;
				return -1;
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
					//		strcpy(date,mysql_row[1]);
					//		interest1 = atof(mysql_row[2]);
							account = atof(mysql_row[cols-1]);
						}
					}
					mysql_free_result(mysql_res);
				}
				sprintf(sql,"select clientid,deal_time,interest,balance from account where clientid = %d;",clientrecv.clientid);
				result = mysql_query(mysql,sql);
				mysql_res = mysql_store_result(mysql);
				cols = mysql_num_fields(mysql_res);                                                      
				if (mysql_res)
				{
					while ((mysql_row = mysql_fetch_row(mysql_res)))
					{
						for (unsigned int i=0; i<cols; ++i)
						{
					//		strcpy(date,mysql_row[1]);
					//		interest1 = atof(mysql_row[2]);
							account1 = atof(mysql_row[cols-1]);
						}
					}
					mysql_free_result(mysql_res);
				}
				if((account1 - clientrecv.captial) < 0)
				{
					clientrecv.relay = TRANSFER_FAIL2;                                               //余额不足，转账失败
					writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
					if(writecnt == -1)
					{
						cerr<<"send error!"<<endl;
						return -1;
					}
					return -1;
				}
				if(account == 0.0)                                                                   //原先没有余额
				{
					GetSystemTime(&clientrecv.intime);
					clientrecv.sum_money = clientrecv.captial;
					sprintf(sql,"insert into account(clientid ,deal_time,inaccount,balance) values(%d,'%d-%d-%d %d:%d:%d',%.2f,%.2f);",clientrecv.toclientid,clientrecv.intime.wYear,clientrecv.intime.wMonth,clientrecv.intime.wDay,clientrecv.intime.wHour,clientrecv.intime.wMinute,clientrecv.intime.wSecond,clientrecv.captial,clientrecv.sum_money);
					result = mysql_query(mysql,sql);
					clientrecv.sum_money = account1-clientrecv.captial;
					sprintf(sql,"insert into account(clientid ,deal_time,outaccount,balance) values(%d,'%d-%d-%d %d:%d:%d',%.2f,%.2f);",clientrecv.clientid,clientrecv.intime.wYear,clientrecv.intime.wMonth,clientrecv.intime.wDay,clientrecv.intime.wHour,clientrecv.intime.wMinute,clientrecv.intime.wSecond,clientrecv.captial,clientrecv.sum_money);
					result = mysql_query(mysql,sql);
					if(result > 0)                                                                   //转账失败
					{
						cout<<mysql_error(mysql)<<endl;
						clientrecv.relay = TRANSFER_FAIL1;
						writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
						if(writecnt == -1)
						{
							cerr<<"send error!"<<endl;
							return -1;
						}
					}
					else
					{
						clientrecv.relay = TRANSFER_OK;												//转账成功
						writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
						if(writecnt == -1)
						{
							cerr<<"send error!"<<endl;
							return -1;
						}
					}
				}
				else                                                                                //转钱操作
				{
					GetSystemTime(&clientrecv.intime);
					clientrecv.sum_money = clientrecv.captial + account;
					sprintf(sql,"insert into account(clientid ,deal_time,inaccount,balance) values(%d,'%d-%d-%d %d:%d:%d',%.2f,%.2f);",clientrecv.toclientid,clientrecv.intime.wYear,clientrecv.intime.wMonth,clientrecv.intime.wDay,clientrecv.intime.wHour,clientrecv.intime.wMinute,clientrecv.intime.wSecond,clientrecv.captial,clientrecv.sum_money);
					result = mysql_query(mysql,sql);
					clientrecv.sum_money = account1 - clientrecv.captial;
					sprintf(sql,"insert into account(clientid ,deal_time,outaccount,balance) values(%d,'%d-%d-%d %d:%d:%d',%.2f,%.2f);",clientrecv.clientid,clientrecv.intime.wYear,clientrecv.intime.wMonth,clientrecv.intime.wDay,clientrecv.intime.wHour,clientrecv.intime.wMinute,clientrecv.intime.wSecond,clientrecv.captial,clientrecv.sum_money);
					result = mysql_query(mysql,sql);
					if(result > 0)                                                                  //转账失败
					{
						cout<<mysql_error(mysql)<<endl;
						clientrecv.relay = TRANSFER_FAIL1;
						writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
						if(writecnt == -1)
						{
							cerr<<"send error!"<<endl;
							return -1;
						}
					}
					else
					{
						clientrecv.relay = TRANSFER_OK;                                            //转账成功
						writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
						if(writecnt == -1)
						{
							cerr<<"send error!"<<endl;
							return -1;
						}
					}
				}
			}
		}
	}
	return 0;
}