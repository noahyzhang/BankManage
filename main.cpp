#include "myhead.h"

<<<<<<< HEAD
MYSQL * mysql = mysql_init(NULL);

int main()
{
	Bankserver ser;
	ser.connect_client();
=======
User clientrecv;
SOCKET socketfd = 0;
int Read = 0;

int main()
{
	Bankclient client;
	client.log_reg_check();
>>>>>>> client
	return 0;
}