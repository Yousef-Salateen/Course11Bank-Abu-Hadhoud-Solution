#pragma once

#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include "clsUser.h"

class clsListUsersScreen :
    protected clsScreen
{
private:
	static void _PrintUserLine(const clsUser& User)
	{
		std::cout << "|" << std::left << std::setw(15) << User.Username();
		std::cout << "|" << std::left << std::setw(40) << User.FullName();
		std::cout << "|" << std::left << std::setw(10) << User.Password();
		std::cout << "|" << std::left << std::setw(15) << User.Phone();
		std::cout << "|" << std::left << std::setw(10) << User.Permissions() << std::endl;
	}

public:

	static void PrintUserList()
	{
		std::vector <clsUser> vUsers = clsUser::GetUserList();

		std::string Title = "User List Screen";
		std::string SubTitle = "(" + std::to_string(vUsers.size()) + ") User(s)";
		_DrawScreenHeader(Title, SubTitle);

		std::cout << "|" << std::left << std::setw(15) << "Username";
		std::cout << "|" << std::left << std::setw(40) << "Full Name";
		std::cout << "|" << std::left << std::setw(10) << "Password";
		std::cout << "|" << std::left << std::setw(15) << "Phone Number";
		std::cout << "|" << std::left << std::setw(10) << "Permissions" << std::endl;
		std::cout << "\n____________________________________________________________________________________________________________________" << std::endl;

		if (vUsers.size())
			for (const clsUser& User : vUsers)
			{
				_PrintUserLine(User);
			}
		else
			std::cout << "No users are found\n";

		std::cout << "\n____________________________________________________________________________________________________________________" << std::endl;
	}

};

