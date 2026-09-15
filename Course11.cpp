#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsMainMenuScreen.h"
using namespace std;

/*static void UpdateClient()
{
	string AccNumber = clsInputValidate::Read<string>("Please Enter a Valid Account Number: ");

	while (!clsBankClient::IsClientExist(AccNumber))
	{
		AccNumber = clsInputValidate::Read <string>("Account Number is not found, enter another one: ");
	}

	clsBankClient Client = clsBankClient::Find(AccNumber);
	Client.Print();

	cout << "\nUpdate Client Info";
	cout << "\n____________________\n";

	ReadClient(Client);

	clsBankClient::enSaveResult SaveResult;

	SaveResult = Client.Save();

	switch (SaveResult)
	{
	default: case clsBankClient::enSaveResult::eFailedEmptyObject:
		cout << "Failed the save, object is empty" << endl;
		break;

	case clsBankClient::enSaveResult::eSucceeded:
		cout << "\nUpdated Successfully\n";
		Client.Print();
		break;
	}
}

static void PrintClientBalanceLine(const clsBankClient& Client)
{
	cout << "|" << left << setw(15) << Client.AccNumber();
	cout << "|" << left << setw(40) << Client.FullName();
	cout << "|" << left << setw(10) << Client.Balance() << endl;
}

static void PrintClientBalanceList()
{
	vector <clsBankClient> vClients = clsBankClient::GetClientList();

	cout << "\n\t\t\t Clients List (" << vClients.size() << ") Client(s).\n";
	cout << "\n____________________________________________________________________________________________________________________" << endl;
	cout << "|" << left << setw(15) << "Account Number";
	cout << "|" << left << setw(40) << "Name";
	cout << "|" << left << setw(10) << "Balance" << endl;
	cout << "\n____________________________________________________________________________________________________________________" << endl;

	double TotalBalances = clsBankClient::GetTotalBalances();

	if (vClients.size())
		for (const clsBankClient& Client : vClients)
		{
			PrintClientLine(Client);
		}
	else
		cout << "No clients are found\n";

	cout << "\n____________________________________________________________________________________________________________________" << endl;

	cout << "\t\t\t\tTotal Balances: " << TotalBalances;
	cout << "\n\t\t\t\t" << clsUtility::NumberToText(TotalBalances) << endl;
}
*/
int main()
{
	clsMainMenuScreen::ShowMainMenuScreen();
}