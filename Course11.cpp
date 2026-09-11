#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

static void ReadClient(clsBankClient& Client)
{
	Client.setFirstName(clsInputValidate::Read<string>("First Name: "));
	Client.setLastName(clsInputValidate::Read<string>("Last Name: "));
	Client.setEmail(clsInputValidate::Read<string>("Email: "));
	Client.setPhone(clsInputValidate::Read<string>("Phone: "));
	Client.setPinCode(clsInputValidate::Read<string>("Pin Code: "));
	Client.setBalance(clsInputValidate::Read<double>("Balance: "));
}

static void UpdateClient()
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

int main()
{
	
}