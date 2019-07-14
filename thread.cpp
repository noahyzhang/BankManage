#include "myhead.h"

//线程处理
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
			case OPEN_ACCOUNT_OK:																								//开户成功
				{
					cout<<"\n\n开户成功！"<<endl;
					cout<<"========================================================================"<<endl;
					cout<<"卡号："<<clientrecv.clientid<<endl;
					cout<<"姓名："<<clientrecv.client_name<<endl;
					cout<<"开户时间："<<clientrecv.intime.wYear<<"."<<clientrecv.intime.wMonth<<"."<<clientrecv.intime.wDay<<endl;
					cout<<"开户银行："<<clientrecv.place_bank<<endl;
					cout<<"当前余额："<<fixed<<setprecision(2)<<clientrecv.sum_money<<"元"<<endl;
					cout<<"========================================================================="<<endl;
					cout<<"请妥善保管账号和密码！"<<endl;
					break;
				}
			case OPEN_ACCOUNT_FAIL:																							  //开户失败
				{
					cout<<"开户失败！"<<endl;
					break;
				}
			case  DEPOSIT_FAIL:																								  //存款失败
				{
					cout<<"\n存款失败！"<<endl;
					cout<<"正在为你处理相关出错，请稍后....."<<endl;
					break;
				}
			case CLOSE_ACCOUNT_FAIL:																						 //销户失败
				{
					cout<<"\n账号或密码有误，销户失败！"<<endl;
					break;
				}
			case CLOSE_ACCOUNT_OK:                                                                                           //销户成功
				{
					cout<<"\n销户成功！"<<endl;
					break;
				}
			case EXIT_OK:																									//退出系统
				{
					cout<<"欢迎使用本系统！"<<endl;
					closesocket(socketfd);
					exit(0);
				}
			case CLIENT_SUCCESS:																							//账号密码匹配成功
				{
					Read = 1;
					break;
				}
			case CLIENT_FAIL:																								//账号密码匹配失败
				{
					cout<<"\n卡号或密码错误，操作失败！"<<endl;
					break;
				}
			case DEPOSIT_OK:                                                                                                 //存钱成功
				{
					cout<<"\n存钱成功！"<<endl;
					cout<<"当前余额为："<<fixed<<setprecision(2)<<clientrecv.sum_money<<"元"<<endl;
					break;
				}
			case WITHDRAWAL_FAIL:																							//取钱失败
				{
					cout<<"\n当前余额不足，取钱失败！"<<endl;
					break;
				}
			case WITHDRAWAL_OK:                                                                                             //取钱成功
				{
					cout<<"\n取钱成功！"<<endl;
					cout<<"当前余额为："<<fixed<<setprecision(2)<<clientrecv.sum_money<<"元"<<endl;
					break;
				}
			case CHANGEPWD_OK:                                                                                              //修改密码成功
				{
					cout<<"\n修改密码成功！"<<endl;
					break;
				}
			case CHANGEPWD_FAIL:                                                                                            //修改密码失败
				{
					cout<<"\n修改密码失败！正在为你处理相关出错信息，请稍后重试！"<<endl;
					break;
				}
			case TRANSFER_FAIL1:                                                                                            //转账失败
				{
					cout<<"\n你所转账的用户不存在，转账失败！"<<endl;
					break;
				}
			case TRANSFER_FAIL2:                                                                                           //余额不足，转账失败
				{
					cout<<"\n你当前余额不足，转账失败！"<<endl;
					break;
				}
			case TRANSFER_OK:                                                                                             //转账成功
				{
					cout<<"\n恭喜转账成功！"<<endl;
					cout<<"接受人账号："<<clientrecv.toclientid<<endl;
					cout<<"接受人姓名："<<clientrecv.toname<<endl;
					cout<<"转账金额："<<fixed<<setprecision(2)<<clientrecv.captial<<"元"<<endl;
					cout<<"当前账户余额为："<<fixed<<setprecision(2)<<clientrecv.sum_money<<"元"<<endl;
					break;
				}
			case LOOK_BALANCE_OK:                                                                                        //查看余额成功
				{
					cout<<"\n您当前的余额："<<fixed<<setprecision(2)<<clientrecv.sum_money<<"元"<<endl;
					break;
				}
			case LOOK_CHECK_OK:
				{
					cout<<clientrecv.clientid<<" "<<setw(12)<<clientrecv.date<<setw(6)<<clientrecv.captial<<setw(6)<<clientrecv.extra_money<<setw(6)<<clientrecv.sum_money<<endl;
					break;
				}
			case LOOK_CHECK_FAIL:
				{
					cout<<"\n当前没有账单信息!"<<endl;
					break;
				}
		}
	}
	return 0;
}