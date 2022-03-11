#pragma once

#include<iostream>
#include<string>
#include<fstream>
using namespace std;


struct Account  
{
	string accNum;
	string client;
	string pin;
	float balance;
};



void LoadState(Account* tabAccounts)
{

	ifstream Myfile;
	Myfile.open("AtmDB.txt");
	string temp;


	for (int i = 0; !Myfile.eof(); i++)
	{
		getline(Myfile, tabAccounts[i].accNum);
		getline(Myfile, tabAccounts[i].client);
		getline(Myfile, tabAccounts[i].pin);
		Myfile >> temp;
		tabAccounts[i].balance = stof(temp);
		Myfile.ignore();
	}
	Myfile.close();
}


int toFindAccNumber(string AccNumber, Account* tabAccounts)
{
	for (int i = 0; tabAccounts[i].accNum != "\0"; i++)
	{
		if (AccNumber == tabAccounts[i].accNum)
		{
			return i;
		}
	}
	return (-1);
}

int GetClientIndex(Account* tabAccounts)
{
	string search;
	int ClientIndex;

	do {
		cout << "Entrez votre numero de compte : ";
		getline(cin >> ws, search);
		ClientIndex = toFindAccNumber(search, tabAccounts);
	} while (ClientIndex == (-1));

	return ClientIndex;
}

void VerifyPassword(short ClientIndex, Account* tabAccounts)
{
	string PIN;

	cout << "\n\tBienvenue " << tabAccounts[ClientIndex].client << endl;
	do {
		cout << "Entrez votre nip : ";
		getline(cin >> ws, PIN);
	} while (PIN != tabAccounts[ClientIndex].pin);

	cout << endl;
}

int Transaction_Menu()
{
	int  choice;

	cout << "Choisir votre Transaction" << endl
		<< "\t1 - Pour Deposer" << endl
		<< "\t2 - Pour Retirer" << endl
		<< "\t3 - Pour Consulter" << endl;
	do
	{
		cout << "Entrez votre choix (1-3) : ";
		cin >> choice;
	} while (choice < 1 || choice > 3);

	cout << endl;

	return choice;
}

float Deposit(int min, int max)
{
	float Deposit;

	do
	{
		cout << "Entrez le montant a deposer : ";
		cin >> Deposit;
	} while (Deposit < min || Deposit > max);

	return Deposit;

}
float Withdraw(int min, int max, float AccBalance)
{
	float Withdrawal;

	do
	{
		cout << "Entrez le montant a retirer $ : ";
		
		cin >> Withdrawal;
		if (Withdrawal < min) {

			cout << "Le montant minimum à retirer est de 20 $\n";
			cout << "Entrez le montant a retirer $ : ";
			cin >> Withdrawal;
		}
		else if (Withdrawal > AccBalance) {
			cout << "Le montant doit être inférieur au solde du compte\n";
			cout << "Entrez le montant a retirer $ : ";
			cin >> Withdrawal;
		}
		else if (((((int)Withdrawal / min) * min) != Withdrawal)) {
			cout << "Le montant doit être un multiple de 20\n";
			cout << "Entrez le montant a retirer $ : ";
			cin >> Withdrawal;
		}
		else if (Withdrawal > max)
		{
			cout << "Le montant maximum par retrait est de 500 $\n";
			cout << "Entrez le montant a retirer $ : ";
			cin >> Withdrawal;
		}
		else {
			cout << "Entrez le montant a retirer $ : ";
			cin >> Withdrawal;
		}

	} while (Withdrawal < min || Withdrawal > AccBalance || Withdrawal > max || ((((int)Withdrawal / min) * min) != Withdrawal));

	return -Withdrawal;

}

void Writingtofile(Account* tabAccounts)
{
	ofstream OutputFile;
	OutputFile.open("AtmDB.txt", ios::in);

	for (int i = 0; tabAccounts[i].accNum != "\0"; i++)
	{
		OutputFile << tabAccounts[i].accNum << endl;
		OutputFile << tabAccounts[i].client << endl;
		OutputFile << tabAccounts[i].pin << endl;
		OutputFile << tabAccounts[i].balance << ((tabAccounts[i + 1].accNum != "\0") ? "\n" : "");
	}
	OutputFile.close();
}

void DisplayConsultation(int CID, Account* tabAccounts)
{
	cout << "\n--- la transaction a reussi --" << endl << endl <<
		"Les infos du compte" << "\n\tNumero : " << tabAccounts[CID].accNum << "\n\tClient : " << tabAccounts[CID].client << "\n\tNip :" <<tabAccounts[CID].pin << "\n\tSolde $ :" << tabAccounts[CID].balance << endl << endl <<
		"Merci d'avoir utiliser nos services" << endl;
}

void DisplayTitle(string Title, bool Stitle)
{
	cout << ((Stitle) ? "\t" : "\t\t");

	if (Stitle)
	{
		for (int i = 0; i != Title.length(); i++)
		{
			cout << ((i == 0 || isspace(Title[i - 1])) ? (char(toupper(Title[i]))) : (Title[i]));
		}
	}
	else
	{
		for (int i = 0; i != Title.length(); i++)
		{
			cout << char(toupper(Title[i]));
		}
	}
	cout << ((Stitle) ? "\n\t" : "\n\t\t");

	for (short i = 0; i != Title.length(); i++)
	{
		cout << "-";
	}
	cout << ((Stitle) ? "\n\n" : "\n");
}
