#include "myhead.h"

//���˵�
int Bankclient::main_menu()
{
	int choice = 0;
	system("cls");
	cout<<"\t\t\t\t*=========================================*"<<endl;
	cout<<"\t\t\t\t|                                         |"<<endl;
	cout<<"\t\t\t\t|   1������         |      2������        |"<<endl;
	cout<<"\t\t\t\t|   3�����         |      4��ȡ��        |"<<endl;
	cout<<"\t\t\t\t|   5��ת��         |      6����ѯ��ϸ    |"<<endl;
	cout<<"\t\t\t\t|   7����ѯ���     |      8���޸�����    |"<<endl;
	cout<<"\t\t\t\t|_________________________________________|"<<endl;
	cout<<"\t\t\t\t|			   0���˳�ϵͳ    |"<<endl;
	cout<<"\t\t\t\t|_________________________________________|"<<endl;
	cout<<"\t\t\t\t��������Ҫ�Ĳ�����";
	cin>>choice;
	while(!(choice >= 0&&choice <= 8))
	{
		cout<<"\t\t\t\t����������������룺";
		cin>>choice;
	}
	return choice;
}
//ִ�����˵�
int Bankclient::main_cmd()
{
	int choice  = 0;
	while(1)
	{
		choice = main_menu();
		switch(choice)
		{
			case 0:
				exit_log();                                              //�˳�����
				break;
			case 1:
				open_account();                                          //����
				break;
			case 2:
				close_account();                                         //����
				break;
			case 3:
				deposit();                                               //���
				break;
			case 4:
				withdrawal();                                            //ȡ��
				break;
			case 5:                                                      //ת��
				transfer();
				break;
			case 6:                                                      //��ѯ��ϸ
				look_check();
				break; 
			case 7:                                                      //��ѯ���
				look_balance();
				break;
			case 8:                                                      //�޸�����
				changepass();
				break;
		}
		getchar();
		getchar();
	}	
}