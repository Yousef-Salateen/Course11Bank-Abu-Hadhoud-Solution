#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include <iostream>
#include "clsInputValidate.h"

class clsUpdateClientScreen :
    protected clsScreen
{
private:
	static void _PrintClient(const clsBankClient& Client)
	{
		std::cout << "\nClient Card:";
		std::cout << "\n_________________";
		std::cout << "\nFirst Name: " << Client.FirstName();
		std::cout << "\nLast Name: " << Client.LastName();
		std::cout << "\nFull Name: " << Client.FullName();
		std::cout << "\nEmail: " << Client.Email();
		std::cout << "\nPhone: " << Client.Phone();
		std::cout << "\nAccount Number: " << Client.AccNumber();
		std::cout << "\nPin Code: " << Client.PinCode();
		std::cout << "\nBalance: " << Client.Balance();
		std::cout << "\n_________________" << std::endl;
	}

	static void _ReadClient(clsBankClient& Client)
	{
		Client.setFirstName(clsInputValidate::Read<std::string>("First Name: "));
		Client.setLastName(clsInputValidate::Read<std::string>("Last Name: "));
		Client.setEmail(clsInputValidate::Read<std::string>("Email: "));
		Client.setPhone(clsInputValidate::Read<std::string>("Phone: "));
		Client.setPinCode(clsInputValidate::Read<std::string>("Pin Code: "));
		Client.setBalance(clsInputValidate::Read<double>("Balance: "));
	}

public:
	static void UpdateClient()
	{
		_DrawScreenHeader("Update Client Screen");
		std::string AccNumber = clsInputValidate::Read<std::string>("Please Enter a Valid Account Number: ");

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			AccNumber = clsInputValidate::Read <std::string>("Account Number is not found, enter another one: ");
		}

		clsBankClient Client = clsBankClient::Find(AccNumber);
		_PrintClient(Client);

		std::cout << "\nUpdate Client Info";
		std::cout << "\n____________________\n";

		_ReadClient(Client);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = Client.Save();

		switch (SaveResult)
		{
		default: case clsBankClient::enSaveResult::eFailedEmptyObject:
			std::cout << "Failed the save, object is empty" << std::endl;
			break;

		case clsBankClient::enSaveResult::eSucceeded:
			std::cout << "\nUpdated Successfully\n";
			_PrintClient(Client);
			break;
		}
	}

};

