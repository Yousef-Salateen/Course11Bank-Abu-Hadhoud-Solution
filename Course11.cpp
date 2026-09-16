#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsLoginScreen.h"
using namespace std;

int main()
{
	while (true)
	{
		clsLoginScreen::Login();
	}
	return 0;
}