#pragma once

#include <iostream>
#include <string>
#include<vector>
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>

class clsUser :
    public clsPerson
{
private:
    enum enMode { _EmptyMode = 0, _UpdateMode, _AddNewMode };
    enMode _Mode;

    std::string _Username;
    std::string _Password;
    int _Permissions = 0;
    bool _MarkedForDelete = false;

    enum enInfoPlace { _eFirstName, _eLastName, _eEmail, _ePhone, _eUsername, _ePassword, _ePermissions };

    static clsUser _ConvertLineToObject(const std::string& Line, const std::string& splitter = "#//#")
    {
        std::vector<std::string> vInfo = clsString::Split(Line, splitter);

        return clsUser(vInfo.at(enInfoPlace::_eFirstName), vInfo.at(enInfoPlace::_eLastName), vInfo.at(enInfoPlace::_eEmail),
            vInfo.at(enInfoPlace::_ePhone), vInfo.at(enInfoPlace::_eUsername), vInfo.at(enInfoPlace::_ePassword),
            std::stoi(vInfo.at(enInfoPlace::_ePermissions)), enMode::_UpdateMode);
    }

    static std::vector<clsUser> _LoadUserDataFromFile()
    {
        std::vector<clsUser> vUsers;

        std::fstream File;
        File.open("Users.txt", std::ios::in);

        if (File.is_open())
        {
            std::string Line;

            while (std::getline(File, Line))
            {
                vUsers.push_back(_ConvertLineToObject(Line));
            }

            File.close();
        }

        return vUsers;
    }

    static std::string _ConvertObjectToLine(const clsUser& User, const std::string& splitter = "#//#")
    {
        std::string Line;

        Line.append(User.FirstName() + splitter);
        Line.append(User.LastName() + splitter);
        Line.append(User.Email() + splitter);
        Line.append(User.Phone() + splitter);
        Line.append(User.Username() + splitter);
        Line.append(User.Password() + splitter);
        Line.append(std::to_string(User.Permissions()));

        return Line;
    }

    static void _SaveUserDataToFile(const std::vector<clsUser>& vUsers)
    {
        std::fstream File;

        File.open("Users.txt", std::ios::out);

        if (File.is_open())
        {
            for (const clsUser& User : vUsers)
            {
                File << _ConvertObjectToLine(User) << std::endl;
            }

            File.close();
        }
    }

    void _AddDataLineToFile(const std::string& Line)
    {
        std::fstream File;

        File.open("Users.txt", std::ios::out | std::ios::app);

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
        std::vector<clsUser> vUsers = _LoadUserDataFromFile();

        for (clsUser& User : vUsers)
        {
            if (User.Username() == this->Username())
            {
                User = *this;
                break;
            }
        }

        _SaveUserDataToFile(vUsers);
    }

    static clsUser _EmptyObject()
    {
        return clsUser("", "", "", "", "", "", 0, enMode::_EmptyMode);
    }

public:
	enum enPermissions { eAll = -1, eListClients = 1, eAddNewClient = 2, eDeleteClient = 4, eUpdateClient = 8,
                        eFindClient = 16, eTransactions = 32, eManageUsers = 64 };

    clsUser(const std::string& FirstName, const std::string& LastName, const std::string& Email, const std::string& Phone,
        const std::string& Username, const std::string& Password, int Permissions, enMode Mode)
        : clsPerson(FirstName, LastName, Email, Phone), _Username(Username), _Password(Password), _Permissions(Permissions), _Mode(Mode)
    {

    }

	void setUsername(const std::string& Username)
	{
		_Username = Username;
	}

    void setPassword(const std::string& Password)
    {
        _Password = Password;
    }

    void setPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    std::string Username() const
    {
        return _Username;
    }

    std::string Password() const
    {
        return _Password;
    }

    int Permissions() const
    {
        return _Permissions;
    }

    bool IsEmpty() const
    {
        return _Mode == enMode::_EmptyMode;
    }

    bool MarkedForDelete() const
    {
        return _MarkedForDelete;
    }

    static clsUser Find(const std::string& Username)
    {
        std::fstream File;

        File.open("Users.txt", std::ios::in);

        if (File.is_open())
        {
            std::string Line;

            while (std::getline(File, Line))
            {
                clsUser User = _ConvertLineToObject(Line);

                if (User.Username() == Username)
                {
                    File.close();
                    return User;
                }
            }
            File.close();
        }

        return _EmptyObject();
    }

    static clsUser Find(const std::string& Username, const std::string& Password)
    {
        std::fstream File;

        File.open("Users.txt", std::ios::in);

        if (File.is_open())
        {
            std::string Line;

            while (std::getline(File, Line))
            {
                clsUser User = _ConvertLineToObject(Line);

                if (User.Username() == Username && User.Password() == Password)
                {
                    File.close();
                    return User;
                }
            }
            File.close();
        }

        return _EmptyObject();
    }

    enum enSaveResult { eFailedEmptyObject = 0, eSucceeded, eFailedExistingUsername };
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
            if (IsUserExist(this->Username()))
            {
                return enSaveResult::eFailedExistingUsername;
            }
            else
            {
                _AddNew();
                this->_Mode = enMode::_UpdateMode;
                return enSaveResult::eSucceeded;
            }
        }
    }

    bool Delete()
    {
        std::vector<clsUser> vUsers = _LoadUserDataFromFile();

        for (clsUser& User : vUsers)
        {
            if (this->Username() == User.Username())
            {
                User._MarkedForDelete = true;
                break;
            }
        }


        _SaveUserDataToFile(vUsers);

        *this = _EmptyObject();

        return true;
    }

    static bool IsUserExist(const std::string& Username)
    {
        clsUser User = Find(Username);

        return !User.IsEmpty();
    }

    static clsUser AddNewObject(const std::string& Username)
    {
        return clsUser("", "", "", "", Username, "", 0, enMode::_AddNewMode);
    }

    static std::vector<clsUser> GetUserList()
    {
        return _LoadUserDataFromFile();
    }
};

