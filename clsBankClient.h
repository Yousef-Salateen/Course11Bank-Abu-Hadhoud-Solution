#pragma once

#include <iostream>
#include <string>
#include<vector>
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>

class clsBankClient :
    public clsPerson
{
private:
    enum enMode { _EmptyMode = 0, _UpdateMode };
    enMode _Mode;

    std::string _AccNumber;
    std::string _PinCode;
    double _Balance;


public:
    clsBankClient(const std::string& FirstName, const std::string& LastName, const std::string& Email, const std::string& Phone,
        const std::string& AccNumber, const std::string& PinCode, double Balance, enMode Mode)
        : clsPerson(FirstName, LastName, Email, Phone), _AccNumber(AccNumber), _PinCode(PinCode), _Balance(Balance), _Mode(Mode)
    {

    }

    void setPinCode(const std::string& PinCode)
    {
        _PinCode = PinCode;
    }

    void setBalance(double Balance)
    {
        _Balance = Balance;
    }

    std::string AccNumber()
    {
        return _AccNumber;
    }

    std::string PinCode()
    {
        return _PinCode;
    }

    double Balance()
    {
        return _Balance;
    }

    bool IsEmpty()
    {
        return _Mode == enMode::_EmptyMode;
    }

    void Print()
    {
        std::cout << "\nClient Card:";
        std::cout << "\n_________________";
        std::cout << "\nFirst Name: " << FirstName();
        std::cout << "\nLast Name: " << LastName();
        std::cout << "\nFull Name: " << FullName();
        std::cout << "\nEmail: " << Email();
        std::cout << "\nPhone: " << Phone();
        std::cout << "\nAccount Number: " << AccNumber();
        std::cout << "\nPin Code: " << PinCode();
        std::cout << "\nBalance: " << Balance();
        std::cout << "\n_________________" << std::endl;
    }

};