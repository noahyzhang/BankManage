#include "myhead.h"

//�޸��������
int Thread::changepass_check()
{
	int writecnt = 0;
	char sql[100] = {0};
	int result = 0;

	sprintf(sql,"update client set password = '%s'where clientid = %d;",clientrecv.clientpwd,clientrecv.clientid);
	result = mysql_query(mysql,sql);
	if(result > 0)                                                                   //�޸�����ʧ��
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
		clientrecv.relay = CHANGEPWD_OK;											 //�޸�����ɹ�
		writecnt = send(clientfd,(char *)&clientrecv,sizeof(User),0);
		if(writecnt == -1)
		{
			cerr<<"send error!"<<endl;
			return -1;
		}
	}
	return 0;
}