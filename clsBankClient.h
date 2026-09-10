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

};