#pragma once

#include <iostream>
#include <iomanip>
#include "Global.h"

class clsScreen
{
protected:
	static void _DrawScreenHeader(const std::string& Title, const std::string& SubTitle = "")
	{
		std::cout << std::setw(37) << std::left << "" << "_________________________\n\n";
		std::cout << std::setw(37) << std::left << "" << Title << "\n";
		if (!SubTitle.empty())
		{
			std::cout << std::setw(37) << std::left << "" << SubTitle << "\n";
		}
		std::cout << std::setw(37) << std::left << "" << "_________________________\n\n";
	}

	static bool _CheckAccessRights(clsUser::enPermissions RequiredPermissions)
	{
		if (!CurrentUser.HasPermission(RequiredPermissions))
		{
			_DrawScreenHeader("Access Denied", "You don't have the required permissions to access this screen.");
			return false;
		}
		return true;
	}
};

