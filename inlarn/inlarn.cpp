// created by isaachhk02 (isaacfhl)

#include <iostream>
#include <Windows.h>
#include <winreg.h>
#include <process.h>
#include "inlarn.h"

using namespace std;

string username = "";
string password = "";
string lang = "english";
HKEY* key;


void Start(string username, string password)
{
    HKEY hKey;
    string subkey_oobe = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OOBE";
    string winlogon = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
    LONG resultado_oobe = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey_oobe.c_str(), 0, KEY_WRITE, &hKey);

    string create_user = "user " + username + " " + password + " /add";
    string add_admin_en = "localgroup Administrators " + username + " /add";
    string add_admin_es = "localgroup Administradores " + username + " /add";
    cout << "Creating user\n";
    
    auto cUser = _execl("C:\\Windows\\System32\\net.exe", create_user.c_str());
    if (cUser) {
        cout << "Created successfully!\n";
    }
    else {
        cout << "ERROR : creating the user sorry :(\n";
    }
    if (lang=="spanish")
    {
        auto addadmin_es_run = _execl("C:\\Windows\\System32\\net.exe", add_admin_es.c_str());
        if (addadmin_es_run)
        {
            cout << "Added successfully!\n";
        }
        if (resultado_oobe == ERROR_SUCCESS) {
            RegSetValueExA(hKey, "LaunchUserOOBE", 0, REG_SZ, (const BYTE*)"0", 0);


            auto open_winlogon = RegOpenKeyExA(HKEY_LOCAL_MACHINE, winlogon.c_str(), 0, KEY_WRITE, &hKey);
            if (open_winlogon == ERROR_SUCCESS) {
                RegSetValueExA(hKey, "AutoAdminLogon", 0, REG_SZ, (const BYTE*)"0", 0);
                RegSetValueExA(hKey, "AutoLogonSID", 0, REG_SZ, (const BYTE*)"", 0);
                RegSetValueExA(hKey, "DefaultUserName", 0, REG_SZ, (const BYTE*)"", 0);
                RegSetValueExA(hKey, "EnableFirstLogonAnimation", 0, REG_DWORD, (const BYTE*)(0), 0);

                cout << "All done!\n";
                RegCloseKey(hKey);
            }
            else {
                cout << "ERROR ";
            }
        }
        else {
            cout << "Error: ";
        }
    }
    else {
        auto addadmin_en_run = _execl("C:\\Windows\\System32\\net.exe", add_admin_en.c_str());
        if (addadmin_en_run)
        {
            cout << "Added successfully!\n";
        }
        if (resultado_oobe == ERROR_SUCCESS) {
            RegSetValueExA(hKey, "LaunchUserOOBE", 0, REG_SZ, (const BYTE*)"0", 0);


            auto open_winlogon = RegOpenKeyExA(HKEY_LOCAL_MACHINE, winlogon.c_str(), 0, KEY_WRITE, &hKey);
            if (open_winlogon == ERROR_SUCCESS) {
                RegSetValueExA(hKey, "AutoAdminLogon", 0, REG_SZ, (const BYTE*)"0", 0);
                RegSetValueExA(hKey, "AutoLogonSID", 0, REG_SZ, (const BYTE*)"", 0);
                RegSetValueExA(hKey, "DefaultUserName", 0, REG_SZ, (const BYTE*)"", 0);
                RegSetValueExA(hKey, "EnableFirstLogonAnimation", 0, REG_DWORD, (const BYTE*)(0), 0);

                cout << "All done!\n";
                RegCloseKey(hKey);
            }
            else {
                cout << "ERROR ";
            }
        }
        else {
            cout << "Error: ";
        }

    }
   




}


int main()
{
    std::cout << "isaachhk02's Local Account Creator and Microsoft Account requirement bypass\n";
    system("pause");

    cin >> lang;
    if (lang == "spanish" or "SPANISH" or "Spanish")
    {
        lang = "spanish";
    }
    else {
        lang = "english";
    }
    cout << "Username:";
    
    cin >> username;
    if (username != "") {
        cout << "Password:";
        cin >> password;
        if (password != "")
        {
            Start(username, password);
        }
        else {
            exit(-1);
        }
    }
    {

    }
}