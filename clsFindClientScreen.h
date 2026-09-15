#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iostream>
#include "clsInputValidate.h"

class clsFindClientScreen :
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

public:
	static void FindClient()
	{
		_DrawScreenHeader("Update Client Screen");
		std::string AccNumber = clsInputValidate::Read<std::string>("Please Enter a Valid Account Number: ");

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			AccNumber = clsInputValidate::Read <std::string>("Account Number is not found, enter another one: ");
		}

		clsBankClient Client = clsBankClient::Find(AccNumber);
		if (!Client.IsEmpty())
		{
			std::cout << "\nClient Found Successfully!\n";
			_PrintClient(Client);
		}
		else
		{
			std::cout << "\nClient Not Found!\n";
		}
	}

};

