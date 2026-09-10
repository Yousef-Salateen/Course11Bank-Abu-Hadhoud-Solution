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

    enum enInfoPlace { _eFirstName, _eLastName, _eEmail, _ePhone, _eAccNumber, _ePinCode, _ePinCode, _eBalance };
    static clsBankClient _ConvertLineToObject(const std::string& Line, const std::string& splitter = "#//#")
    {
        std::vector<std::string> vInfo = clsString::Split(Line, splitter);

        return clsBankClient(vInfo.at(enInfoPlace::_eFirstName), vInfo.at(enInfoPlace::_eLastName), vInfo.at(enInfoPlace::_eEmail),
            vInfo.at(enInfoPlace::_ePhone), vInfo.at(enInfoPlace::_eAccNumber), vInfo.at(enInfoPlace::_ePinCode),
            std::stod(vInfo.at(enInfoPlace::_eBalance)), enMode::_UpdateMode);
    }

    static clsBankClient _EmptyObject()
    {
        return clsBankClient("", "", "", "", "", "", 0, enMode::_EmptyMode);
    }

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

    static clsBankClient Find(const std::string& AccNumber)
    {
        std::fstream File;

        File.open("Clients.txt", std::ios::in);

        if (File.is_open())
        {
            std::string Line;

            while (std::getline(File, Line))
            {
                clsBankClient Client = _ConvertLineToObject(Line);

                if (Client.AccNumber() == AccNumber)
                {
                    File.close();
                    return Client;
                }
            }
            File.close();
        }

        return _EmptyObject();
    }

    static clsBankClient Find(const std::string& AccNumber, const std::string& PinCode)
    {
        std::fstream File;

        File.open("Clients.txt", std::ios::in);

        if (File.is_open())
        {
            std::string Line;

            while (std::getline(File, Line))
            {
                clsBankClient Client = _ConvertLineToObject(Line);

                if (Client.AccNumber() == AccNumber && Client.PinCode() == PinCode)
                {
                    File.close();
                    return Client;
                }
            }
            File.close();
        }

        return _EmptyObject();
    }

    static bool IsClientExist(const std::string& AccNumber)
    {
        clsBankClient Client = Find(AccNumber);

        return !Client.IsEmpty();
    }
};