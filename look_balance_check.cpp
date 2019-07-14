#include "myhead.h"

//查询余额
int Thread::look_balance_check()
{
	int writecnt = 0;
	int result = 0;
	char sql[200] = {0};                    //sql语句存放
	float account = 0;                      //存放长刺余额
	char date[100] = {0};                   //暂时存放上一次的日期
	float interest1 = 0;                    //暂时存放上一次的利息
	float interest = 0;		                //计算本次的利息

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
					clientrecv.sum_money = atof(mysql_row[cols-1]);
				}
			}
			mysql_free_result(mysql_res);
		}
		clientrecv.relay = LOOK_BALANCE_OK;
		writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"send error!"<<endl;
			return -1;
		}
	}
	return 0;
}