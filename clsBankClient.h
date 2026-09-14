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
    enum enMode { _EmptyMode = 0, _UpdateMode, _AddNewMode};
    enMode _Mode;

    std::string _AccNumber;
    std::string _PinCode;
    double _Balance;

    enum enInfoPlace { _eFirstName, _eLastName, _eEmail, _ePhone, _eAccNumber, _ePinCode, _eBalance };

    static clsBankClient _ConvertLineToObject(const std::string& Line, const std::string& splitter = "#//#")
    {
        std::vector<std::string> vInfo = clsString::Split(Line, splitter);

        return clsBankClient(vInfo.at(enInfoPlace::_eFirstName), vInfo.at(enInfoPlace::_eLastName), vInfo.at(enInfoPlace::_eEmail),
            vInfo.at(enInfoPlace::_ePhone), vInfo.at(enInfoPlace::_eAccNumber), vInfo.at(enInfoPlace::_ePinCode),
            std::stod(vInfo.at(enInfoPlace::_eBalance)), enMode::_UpdateMode);
    }

    static std::vector<clsBankClient> _LoadClientDataFromFile()
    {
        std::vector<clsBankClient> vClients;

        std::fstream File;
        File.open("Clients.txt", std::ios::in);

        if (File.is_open())
        {
            std::string Line;

            while (std::getline(File, Line))
            {
                vClients.push_back(_ConvertLineToObject(Line));
            }

            File.close();
        }

        return vClients;
    }

    static std::string _ConvertObjectToLine(const clsBankClient& Client, const std::string& splitter = "#//#")
    {
        std::string Line;

        Line.append(Client.FirstName() + splitter);
        Line.append(Client.LastName() + splitter);
        Line.append(Client.Email() + splitter);
        Line.append(Client.Phone() + splitter);
        Line.append(Client.AccNumber() + splitter);
        Line.append(Client.PinCode() + splitter);
        Line.append(std::to_string(Client.Balance()));

        return Line;
    }

    static void _SaveClientDataToFile(const std::vector<clsBankClient>& vClients)
    {
        std::fstream File;

        File.open("Clients.txt", std::ios::out);

        if (File.is_open())
        {
            for (const clsBankClient& Client : vClients)
            {
                File << _ConvertObjectToLine(Client) << std::endl;
            }

            File.close();
        }
    }

    void _AddDataLineToFile(const std::string& Line)
    {
        std::fstream File;

        File.open("Clients.txt", std::ios::out | std::ios::app);

        if (File.is_open())
        {
            File << Line << std::endl;
            File.close();
        }
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertObjectToLine(*this));
    }

    void _Update() const
    {
        std::vector<clsBankClient> vClients = _LoadClientDataFromFile();

        for (clsBankClient& Client : vClients)
        {
            if (Client.AccNumber() == this->AccNumber())
            {
                Client = *this;
                break;
            }
        }

        _SaveClientDataToFile(vClients);
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

    std::string AccNumber() const
    {
        return _AccNumber;
    }

    std::string PinCode() const
    {
        return _PinCode;
    }

    double Balance() const
    {
        return _Balance;
    }

    bool IsEmpty() const
    {
        return _Mode == enMode::_EmptyMode;
    }

    void Print() const
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

    enum enSaveResult { eFailedEmptyObject = 0, eSucceeded, eFailedExistingAccNumber};
    enSaveResult Save()
    {
        switch (_Mode)
        {
        default: case enMode::_EmptyMode:
            return enSaveResult::eFailedEmptyObject;

        case enMode::_UpdateMode:
            _Update();
            return enSaveResult::eSucceeded;

        case enMode::_AddNewMode:
            if (IsClientExist(this->AccNumber()))
            {
                return enSaveResult::eFailedExistingAccNumber;
            }
            else
            {
                _AddNew();
                this->_Mode = enMode::_UpdateMode;
                return enSaveResult::eSucceeded;
            }
        }
    }

    static bool IsClientExist(const std::string& AccNumber)
    {
        clsBankClient Client = Find(AccNumber);

        return !Client.IsEmpty();
    }
};