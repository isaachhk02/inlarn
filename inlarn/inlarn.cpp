// created by isaachhk02 (isaacfhl)

#include <iostream>
#include <Windows.h>
#include <winreg.h>

#include <process.h>
#include "inlarn.h"
#include <LM.h>

#pragma comment(lib, "netapi32.lib")
using namespace std;
string username = "";
string password = "";
USER_INFO_1 userInfo;


HKEY hKey;

auto subkey_oobe = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OOBE";
auto winlogon = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
auto resultado_oobe = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey_oobe, 0, KEY_WRITE, &hKey);
auto open_winlogon = RegOpenKeyExA(HKEY_LOCAL_MACHINE, winlogon, 0, KEY_WRITE, &hKey);



void Start(string username, string password)
{
    const char* useroobe = "LaunchUserOOBE";
    USER_INFO_1 userInfo;
    userInfo.usri1_name = (LPWSTR)username.c_str();
    userInfo.usri1_password = (LPWSTR)password.c_str();
    userInfo.usri1_priv = USER_PRIV_ADMIN;
    userInfo.usri1_home_dir = NULL;
    userInfo.usri1_flags = UF_SCRIPT;
    userInfo.usri1_comment = NULL;
    userInfo.usri1_script_path = NULL;
    cout << "Creating user\n";
    NET_API_STATUS status = NetUserAdd(NULL, 1, (LPBYTE)&userInfo, 0);

    if (status == NERR_Success) {
        cout << "Created successfully!\n";
    }
    else {
        cout << &R"(ERROR : creating the user sorry :()" [status];
    }
    if (resultado_oobe == ERROR_SUCCESS) {
        RegSetValueExA(hKey, useroobe, 0, REG_DWORD, (const BYTE*)0, NULL);
    }
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
    int main()
    {
        std::cout << "isaachhk02's Local Account Creator and Microsoft Account requirement bypass\n";
        system("pause");
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
   }
    