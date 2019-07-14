#include "myhead.h"

//���
int Thread::deposit_check()
{
	int writecnt = 0;
	int result = 0;                         
	char sql[200] = {0};                    //sql�����
	float account = 0;                      //��ų������
	char date[100] = {0};                   //��ʱ�����һ�ε�����
	float interest1 = 0;                    //��ʱ�����һ�ε���Ϣ
	float interest = 0;		                //���㱾�ε���Ϣ

	MYSQL_RES* mysql_res;
	MYSQL_FIELD* mysql_field;
	MYSQL_ROW mysql_row;
	unsigned int cols;
	int flag = 0;

	sprintf(sql,"select clientid,deal_time,interest,balance from account where clientid = %d;",clientrecv.clientid);
	result = mysql_query(mysql,sql);
	mysql_res = mysql_store_result(mysql); 
	if(result != 0)
	{
		cout<<mysql_error(mysql)<<endl;
		cout<<"��ѯʧ�ܣ�"<<endl;
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
					strcpy(date,mysql_row[1]);
			//		interest1 = atof(mysql_row[2]);
					account = atof(mysql_row[cols-1]);
				}
			}
			mysql_free_result(mysql_res);
		}
		if(account == 0.0)                                                                   //ԭ��û�����
		{
			GetSystemTime(&clientrecv.intime);
			clientrecv.sum_money = clientrecv.captial;
			sprintf(sql,"insert into account(clientid ,deal_time,inaccount,balance) values(%d,'%d-%d-%d %d:%d:%d',%.2f,%.2f);",clientrecv.clientid,clientrecv.intime.wYear,clientrecv.intime.wMonth,clientrecv.intime.wDay,clientrecv.intime.wHour,clientrecv.intime.wMinute,clientrecv.intime.wSecond,clientrecv.captial,clientrecv.sum_money);
			result = mysql_query(mysql,sql);
			if(result > 0)                                                                   //���ʧ��
			{
				cout<<mysql_error(mysql)<<endl;
				clientrecv.relay = DEPOSIT_FAIL;
				writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
				if(writecnt == -1)
				{
					cerr<<"send error!"<<endl;
					return -1;
				}
			}
			else
			{
				clientrecv.relay = DEPOSIT_OK;
				writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
				if(writecnt == -1)
				{
					cerr<<"send error!"<<endl;
					return -1;
				}
			}
		}
		else                                                                                //��Ǯ����
		{
			GetSystemTime(&clientrecv.intime);
			clientrecv.sum_money = clientrecv.captial+account;
			sprintf(sql,"insert into account(clientid ,deal_time,inaccount,balance) values(%d,'%d-%d-%d %d:%d:%d',%.2f,%.2f);",clientrecv.clientid,clientrecv.intime.wYear,clientrecv.intime.wMonth,clientrecv.intime.wDay,clientrecv.intime.wHour,clientrecv.intime.wMinute,clientrecv.intime.wSecond,clientrecv.captial,clientrecv.sum_money);
			result = mysql_query(mysql,sql);
			if(result > 0)                                                                  //���ʧ��
			{
				cout<<mysql_error(mysql)<<endl;
				clientrecv.relay = DEPOSIT_FAIL;
				writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
				if(writecnt == -1)
				{
					cerr<<"send error!"<<endl;
					return -1;
				}
			}
			else
			{
				clientrecv.relay = DEPOSIT_OK;
				writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
				if(writecnt == -1)
				{
					cerr<<"send error!"<<endl;
					return -1;
				}
			}
		}
	}
	return 0;
}