#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iostream>
#include <iomanip>
#include "clsDepositScreen.h"

class clsTransactionMenu :
    protected clsScreen
{
private:
	enum enTransactionMenuOptions
	{
		eDeposit = 1,
		eWithdraw,
		eTotalBalance,
		eExit
	};

	static void _WaitForEnter()
	{
		std::cout << "\nPress Enter to continue...";
		std::cin.get();
	}

	static enTransactionMenuOptions _ReadTransactionMenuOption()
	{
		return static_cast<enTransactionMenuOptions>(clsInputValidate::ReadInRange<int>("\nChoose what do you want to do? [1 to 4] : ",
			1, enTransactionMenuOptions::eExit));
	}

	static void _ClearScreen()
	{
		std::cout << "\033[2J\033[1;1H";
	}

	static void _PerformTransactionMenuOption(enTransactionMenuOptions TransactionMenuOption)
	{
		switch (TransactionMenuOption)
		{
		case enTransactionMenuOptions::eDeposit:
			_ShowDepositScreen();
			_WaitForEnter();
			break;
		case enTransactionMenuOptions::eWithdraw:
			_ShowWithdrawScreen();
			_WaitForEnter();
			break;
		case enTransactionMenuOptions::eTotalBalance:
			_ShowTotalBalanceScreen();
			_WaitForEnter();
			break;
		case enTransactionMenuOptions::eExit:
			_ShowExitScreen();
			_WaitForEnter();
			break;
		default:
			std::cout << "Invalid option! Please try again.\n";
			break;
		}
	}

	static void _ShowDepositScreen()
	{
		_ClearScreen();
		clsDepositScreen::Deposit();
	}

	static void _ShowWithdrawScreen()
	{
		_ClearScreen();
		_DrawScreenHeader("WITHDRAW SCREEN");
	}

	static void _ShowTotalBalanceScreen()
	{
		_ClearScreen();
		_DrawScreenHeader("TOTAL BALANCE SCREEN");
	}

	static void _ShowExitScreen()
	{
		_ClearScreen();
		_DrawScreenHeader("EXIT SCREEN");
	}

public:
	static void ShowTransactionScreen()
	{
		enTransactionMenuOptions MainMenuOption;
		do
		{
			_ClearScreen();
			_DrawScreenHeader("TRANSACTION MENU SCREEN");
			std::cout << std::setw(37) << std::left << "" << "[1] Deposit.\n";
			std::cout << std::setw(37) << std::left << "" << "[2] Withdraw.\n";
			std::cout << std::setw(37) << std::left << "" << "[3] Total Balance.\n";
			std::cout << std::setw(37) << std::left << "" << "[4] Exit.\n";

			MainMenuOption = _ReadTransactionMenuOption();
			_PerformTransactionMenuOption(MainMenuOption);
		} while (MainMenuOption != enTransactionMenuOptions::eExit);

	}
};

