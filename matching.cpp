#include "myhead.h"

//∆•≈‰’À∫≈∫Õ√‹¬Î
int Thread::matching_check()
{
	int writecnt = 0;
	int result = 0;
	char sql[100] = {0};
	MYSQL_RES* mysql_res;
	MYSQL_FIELD* mysql_field;
	MYSQL_ROW mysql_row;
	unsigned int cols;
	int flag = 0;

	sprintf(sql,"select clientid,password from client where clientid = %d;",clientrecv.clientid);
	result = mysql_query(mysql, sql);
	mysql_res = mysql_store_result(mysql);                                                
	if (result != 0)                                                                //≤È—Ø ß∞‹
	{
		cout<<mysql_error(mysql)<<endl;
		clientrecv.relay = CLIENT_FAIL;
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
					if(clientrecv.clientid == atoi(mysql_row[0])&&strcmp(clientrecv.clientpwd,mysql_row[1]) == 0)   //≈–∂œ’Àªß√‹¬Î «∑Ò’˝»∑
					{
						flag = 1;
					}
				}
			}
			mysql_free_result(mysql_res);
		}
		if(flag == 1)                                                            //∆•≈‰≥…π¶
		{
			clientrecv.relay = CLIENT_SUCCESS;
			writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
			if(writecnt == -1)
			{
				cerr<<"send error!"<<endl;
				return -1;
			}
		}
		else
		{
			clientrecv.relay = CLIENT_FAIL;                                      //∆•≈‰ ß∞‹
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