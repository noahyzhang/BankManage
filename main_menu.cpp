#include "myhead.h"

//主菜单
int Bankclient::main_menu()
{
	int choice = 0;
	system("cls");
	cout<<"\t\t\t\t*=========================================*"<<endl;
	cout<<"\t\t\t\t|                                         |"<<endl;
	cout<<"\t\t\t\t|   1、开户         |      2、销户        |"<<endl;
	cout<<"\t\t\t\t|   3、存款         |      4、取款        |"<<endl;
	cout<<"\t\t\t\t|   5、转账         |      6、查询明细    |"<<endl;
	cout<<"\t\t\t\t|   7、查询余额     |      8、修改密码    |"<<endl;
	cout<<"\t\t\t\t|_________________________________________|"<<endl;
	cout<<"\t\t\t\t|			   0、退出系统    |"<<endl;
	cout<<"\t\t\t\t|_________________________________________|"<<endl;
	cout<<"\t\t\t\t请输入你要的操作：";
	cin>>choice;
	while(!(choice >= 0&&choice <= 8))
	{
		cout<<"\t\t\t\t输入错误，请重新输入：";
		cin>>choice;
	}
	return choice;
}
//执行主菜单
int Bankclient::main_cmd()
{
	int choice  = 0;
	while(1)
	{
		choice = main_menu();
		switch(choice)
		{
			case 0:
				exit_log();                                              //退出处理
				break;
			case 1:
				open_account();                                          //开户
				break;
			case 2:
				close_account();                                         //销户
				break;
			case 3:
				deposit();                                               //存款
				break;
			case 4:
				withdrawal();                                            //取款
				break;
			case 5:                                                      //转账
				transfer();
				break;
			case 6:                                                      //查询明细
				look_check();
				break; 
			case 7:                                                      //查询余额
				look_balance();
				break;
			case 8:                                                      //修改密码
				changepass();
				break;
		}
		getchar();
		getchar();
	}	
}