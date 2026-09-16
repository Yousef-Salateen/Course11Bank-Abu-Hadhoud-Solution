#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsMainMenuScreen.h"

class clsLoginScreen :
    protected clsScreen
{
private:
    static void _Login()
    {
		std::string Username = clsInputValidate::Read<std::string>("Please Enter Your Username: ");
		std::string Password = clsInputValidate::Read<std::string>("Please Enter Your Password: ");
		CurrentUser = clsUser::Find(Username, Password);

		while (CurrentUser.IsEmpty())
		{
			std::cout << "\nInvalid Username or Password, please try again.\n";
			Username = clsInputValidate::Read<std::string>("Please Enter Your Username: ");
			Password = clsInputValidate::Read<std::string>("Please Enter Your Password: ");
			CurrentUser = clsUser::Find(Username, Password);
		}

		clsMainMenuScreen::ShowMainMenuScreen();
    }

public:
	static void Login()
	{
		_DrawScreenHeader("Login Screen");
		_Login();
	}
};

