#pragma once

#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"

class clsMainMenuScreen :
    protected clsScreen
{
private:
	enum enMainMenuOptions
	{
		eShowClientsList = 1,
		eAddNewClient,
		eDeleteClient,
		eUpdateClient,
		eFindClient,
		eShowTransactionsScreen,
		eManageUsersScreen,
		eExit
	};

	static enMainMenuOptions _ReadMainMenuOption()
	{
		return static_cast<enMainMenuOptions>(clsInputValidate::ReadInRange<int>("\nChoose what do you want to do? [1 to 8] : ",
			1, enMainMenuOptions::eExit));
	}

	static void _ClearScreen()
	{
		std::cout << "\033[2J\033[1;1H";
	}

	static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption)
	{
		switch (MainMenuOption)
		{
		case enMainMenuOptions::eShowClientsList:
			_ShowClientsListScreen();
			_WaitForEnter();
			break;
		case enMainMenuOptions::eAddNewClient:
			_ShowAddNewClientScreen();
			_WaitForEnter();
			break;
		case enMainMenuOptions::eDeleteClient:
			_ShowDeleteClientScreen();
			_WaitForEnter();
			break;
		case enMainMenuOptions::eUpdateClient:
			_ShowUpdateClientScreen();
			_WaitForEnter();
			break;
		case enMainMenuOptions::eFindClient:
			_ShowFindClientScreen();
			_WaitForEnter();
			break;
		case enMainMenuOptions::eShowTransactionsScreen:
			_ShowTransactionsScreen();
			_WaitForEnter();
			break;
		case enMainMenuOptions::eManageUsersScreen:
			_ShowManageUsersScreen();
			_WaitForEnter();
			break;
		case enMainMenuOptions::eExit:
			_ShowExitScreen();
			_WaitForEnter();
			break;
		default:
			std::cout << "Invalid option! Please try again.\n";
			break;
		}
	}

	static void _ShowClientsListScreen()
	{
		_ClearScreen();
		clsClientListScreen::PrintClientList();
	}

	static void _ShowAddNewClientScreen()
	{
		_ClearScreen();
		clsAddNewClientScreen::AddClient();
	}

	static void _ShowDeleteClientScreen()
	{
		_ClearScreen();
		_DrawScreenHeader("DELETE CLIENT SCREEN");
		std::cout << "This is where the delete client functionality will be implemented.\n";
	}

	static void _ShowUpdateClientScreen()
	{
		_ClearScreen();
		_DrawScreenHeader("UPDATE CLIENT SCREEN");
		std::cout << "This is where the update client functionality will be implemented.\n";
	}

	static void _ShowFindClientScreen()
	{
		_ClearScreen();
		_DrawScreenHeader("FIND CLIENT SCREEN");
		std::cout << "This is where the find client functionality will be implemented.\n";
	}

	static void _ShowTransactionsScreen()
	{
		_ClearScreen();
		_DrawScreenHeader("SHOW TRANSACTIONS SCREEN");
		std::cout << "This is where the transactions will be displayed.\n";
	}

	static void _ShowManageUsersScreen()
	{
		_ClearScreen();
		_DrawScreenHeader("MANAGE USERS SCREEN");
		std::cout << "This is where the manage users functionality will be implemented.\n";
	}

	static void _ShowExitScreen()
	{
		_ClearScreen();
		std::cout << "Exiting the application. Goodbye!\n";
	}

	static void _WaitForEnter()
	{
		std::cin.get();
	}

public:
	static void ShowMainMenuScreen()
	{
		enMainMenuOptions MainMenuOption;
		do
		{
			_ClearScreen();
			_DrawScreenHeader("MAIN MENU SCREEN");
			std::cout << std::setw(37) << std::left << "" << "[1] Show Clients List.\n";
			std::cout << std::setw(37) << std::left << "" << "[2] Add New Client.\n";
			std::cout << std::setw(37) << std::left << "" << "[3] Delete Client.\n";
			std::cout << std::setw(37) << std::left << "" << "[4] Update Client Info.\n";
			std::cout << std::setw(37) << std::left << "" << "[5] Find Client.\n";
			std::cout << std::setw(37) << std::left << "" << "[6] Show Transactions Screen.\n";
			std::cout << std::setw(37) << std::left << "" << "[7] Manage Users Screen.\n";
			std::cout << std::setw(37) << std::left << "" << "[8] Exit.\n";

			MainMenuOption = _ReadMainMenuOption();
			_PerformMainMenuOption(MainMenuOption);
		} while (MainMenuOption != enMainMenuOptions::eExit);

	}
};

