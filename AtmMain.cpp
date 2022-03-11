#include"AtmHeader.h"

int main()
{
	int ClientIndex;
	Account Accounts[60];
	DisplayTitle("banque royale", 0);
	DisplayTitle("guichet automatique Bancarie", 1);
	LoadState(Accounts);
	ClientIndex = GetClientIndex(Accounts);
	VerifyPassword(ClientIndex, Accounts);
	switch (Transaction_Menu())
	{
	case 1:
		Accounts[ClientIndex].balance += Deposit(2, 20000);
		Writingtofile( Accounts);
		break;
	case 2:
		Accounts[ClientIndex].balance += Withdraw(20, 500, Accounts[ClientIndex].balance);
		Writingtofile(Accounts);
		break;
	}

	DisplayConsultation(ClientIndex, Accounts);

	system("pause");
}
