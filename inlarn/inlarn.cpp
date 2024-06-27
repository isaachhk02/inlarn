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
    const char* subkey_oobe = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OOBE";
    const char* winlogon = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
    LONG resultado_oobe = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey_oobe, 0, KEY_WRITE, &hKey);

    string create_user = username  + " " + password  + " /add";
    string add_admin_en = "localgroup administrators" + username + " /add";
    string add_admin_es = "localgroup administradores" + username + " /add";
    cout << "Creating user\n";
    
    _execl("C:\\Windows\\System32\\net.exe", create_user.c_str());
    if (lang=="spanish")
    {
        _execl("C:\\Windows\\System32\\net.exe", add_admin_es.c_str());
    }
    else {
        _execl("C:\\Windows\\System32\\net.exe", add_admin_en.c_str());
    }
    if (resultado_oobe == ERROR_SUCCESS) {
        RegSetValueExA(hKey, "LaunchUserOOBE", 0, REG_SZ, (const BYTE*)"0", 0);
        

        auto open_winlogon = RegOpenKeyExA(HKEY_LOCAL_MACHINE, winlogon, 0, KEY_WRITE, &hKey);
        if (open_winlogon == ERROR_SUCCESS) {
            RegSetValueExA(hKey, "AutoAdminLogon", 0, REG_SZ, (const BYTE*)"0", 0);
            RegSetValueExA(hKey, "AutoLogonSID", 0, REG_SZ, (const BYTE*)"", 0);
            RegSetValueExA(hKey, "DefaultUserName", 0, REG_SZ, (const BYTE*)"", 0);
            RegSetValueExA(hKey, "EnableFirstLogonAnimation", 0, REG_DWORD, (const BYTE*)(0), 0);
        }
        else {
            cout << "ERROR " + open_winlogon;
            exit(-1);
        }
    }
    else {
        cout << "Error: " + resultado_oobe;
        exit(-1);
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
    cin >> username;
    if (username != "") {
        cin >> password;
        if (password != "")
        {
            Start(username, password);
        }
        else {
            main();
        }
    }
    {

    }
}