#pragma once

#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"

class clsClientListScreen :
    protected clsScreen
{
private:
	static void _PrintClientLine(const clsBankClient& Client)
	{
		std::cout << "|" << std::left << std::setw(15) << Client.AccNumber();
		std::cout << "|" << std::left << std::setw(40) << Client.FullName();
		std::cout << "|" << std::left << std::setw(10) << Client.PinCode();
		std::cout << "|" << std::left << std::setw(15) << Client.Phone();
		std::cout << "|" << std::left << std::setw(10) << Client.Balance() << std::endl;
	}

public:

	static void PrintClientList()
	{
		std::vector <clsBankClient> vClients = clsBankClient::GetClientList();

		std::string Title = "Client List Screen";
		std::string SubTitle = "(" + std::to_string(vClients.size()) + ") Client(s)";
		_DrawScreenHeader(Title, SubTitle);

		std::cout << "|" << std::left << std::setw(15) << "Account Number";
		std::cout << "|" << std::left << std::setw(40) << "Name";
		std::cout << "|" << std::left << std::setw(10) << "Pin Code";
		std::cout << "|" << std::left << std::setw(15) << "Phone Number";
		std::cout << "|" << std::left << std::setw(10) << "Balance" << std::endl;
		std::cout << "\n____________________________________________________________________________________________________________________" << std::endl;

		if (vClients.size())
			for (const clsBankClient& Client : vClients)
			{
				_PrintClientLine(Client);
			}
		else
			std::cout << "No clients are found\n";

		std::cout << "\n____________________________________________________________________________________________________________________" << std::endl;
	}

};

