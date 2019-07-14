#include "myhead.h"

//�̴߳���
DWORD WINAPI Bankclient::read_from_server(LPVOID fd)
{
	int recvcnt;
	while(1)
	{
		recvcnt = recv(socketfd,(char *)&clientrecv,sizeof(User),0);
		if(recvcnt == SOCKET_ERROR)
		{
			cerr<<"read error"<<endl;
			break;
		}
		if(recvcnt == 0)
		{
			cout<<"client close"<<endl;
			break;
		}
		switch(clientrecv.relay)
		{
			case OPEN_ACCOUNT_OK:																								//�����ɹ�
				{
					cout<<"\n\n�����ɹ���"<<endl;
					cout<<"========================================================================"<<endl;
					cout<<"���ţ�"<<clientrecv.clientid<<endl;
					cout<<"������"<<clientrecv.client_name<<endl;
					cout<<"����ʱ�䣺"<<clientrecv.intime.wYear<<"."<<clientrecv.intime.wMonth<<"."<<clientrecv.intime.wDay<<endl;
					cout<<"�������У�"<<clientrecv.place_bank<<endl;
					cout<<"��ǰ��"<<fixed<<setprecision(2)<<clientrecv.sum_money<<"Ԫ"<<endl;
					cout<<"========================================================================="<<endl;
					cout<<"�����Ʊ����˺ź����룡"<<endl;
					break;
				}
			case OPEN_ACCOUNT_FAIL:																							  //����ʧ��
				{
					cout<<"����ʧ�ܣ�"<<endl;
					break;
				}
			case  DEPOSIT_FAIL:																								  //���ʧ��
				{
					cout<<"\n���ʧ�ܣ�"<<endl;
					cout<<"����Ϊ�㴦����س������Ժ�....."<<endl;
					break;
				}
			case CLOSE_ACCOUNT_FAIL:																						 //����ʧ��
				{
					cout<<"\n�˺Ż�������������ʧ�ܣ�"<<endl;
					break;
				}
			case CLOSE_ACCOUNT_OK:                                                                                           //�����ɹ�
				{
					cout<<"\n�����ɹ���"<<endl;
					break;
				}
			case EXIT_OK:																									//�˳�ϵͳ
				{
					cout<<"��ӭʹ�ñ�ϵͳ��"<<endl;
					closesocket(socketfd);
					exit(0);
				}
			case CLIENT_SUCCESS:																							//�˺�����ƥ��ɹ�
				{
					Read = 1;
					break;
				}
			case CLIENT_FAIL:																								//�˺�����ƥ��ʧ��
				{
					cout<<"\n���Ż�������󣬲���ʧ�ܣ�"<<endl;
					break;
				}
			case DEPOSIT_OK:                                                                                                 //��Ǯ�ɹ�
				{
					cout<<"\n��Ǯ�ɹ���"<<endl;
					cout<<"��ǰ���Ϊ��"<<fixed<<setprecision(2)<<clientrecv.sum_money<<"Ԫ"<<endl;
					break;
				}
			case WITHDRAWAL_FAIL:																							//ȡǮʧ��
				{
					cout<<"\n��ǰ���㣬ȡǮʧ�ܣ�"<<endl;
					break;
				}
			case WITHDRAWAL_OK:                                                                                             //ȡǮ�ɹ�
				{
					cout<<"\nȡǮ�ɹ���"<<endl;
					cout<<"��ǰ���Ϊ��"<<fixed<<setprecision(2)<<clientrecv.sum_money<<"Ԫ"<<endl;
					break;
				}
			case CHANGEPWD_OK:                                                                                              //�޸�����ɹ�
				{
					cout<<"\n�޸�����ɹ���"<<endl;
					break;
				}
			case CHANGEPWD_FAIL:                                                                                            //�޸�����ʧ��
				{
					cout<<"\n�޸�����ʧ�ܣ�����Ϊ�㴦����س�����Ϣ�����Ժ����ԣ�"<<endl;
					break;
				}
			case TRANSFER_FAIL1:                                                                                            //ת��ʧ��
				{
					cout<<"\n����ת�˵��û������ڣ�ת��ʧ�ܣ�"<<endl;
					break;
				}
			case TRANSFER_FAIL2:                                                                                           //���㣬ת��ʧ��
				{
					cout<<"\n�㵱ǰ���㣬ת��ʧ�ܣ�"<<endl;
					break;
				}
			case TRANSFER_OK:                                                                                             //ת�˳ɹ�
				{
					cout<<"\n��ϲת�˳ɹ���"<<endl;
					cout<<"�������˺ţ�"<<clientrecv.toclientid<<endl;
					cout<<"������������"<<clientrecv.toname<<endl;
					cout<<"ת�˽�"<<fixed<<setprecision(2)<<clientrecv.captial<<"Ԫ"<<endl;
					cout<<"��ǰ�˻����Ϊ��"<<fixed<<setprecision(2)<<clientrecv.sum_money<<"Ԫ"<<endl;
					break;
				}
			case LOOK_BALANCE_OK:                                                                                        //�鿴���ɹ�
				{
					cout<<"\n����ǰ����"<<fixed<<setprecision(2)<<clientrecv.sum_money<<"Ԫ"<<endl;
					break;
				}
			case LOOK_CHECK_OK:
				{
					cout<<clientrecv.clientid<<" "<<setw(12)<<clientrecv.date<<setw(6)<<clientrecv.captial<<setw(6)<<clientrecv.extra_money<<setw(6)<<clientrecv.sum_money<<endl;
					break;
				}
			case LOOK_CHECK_FAIL:
				{
					cout<<"\n��ǰû���˵���Ϣ!"<<endl;
					break;
				}
		}
	}
	return 0;
}