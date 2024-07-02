// created by isaachhk02 (isaacfhl)

#include <iostream>
#include <windows.h>
#include <winreg.h>

#include "inlarn.h"
#include <lmaccess.h>

#pragma comment(lib, "netapi32.lib")
using namespace std;
string username;
string password;
string group;
int lang;
string lang_selected;
USER_INFO_1 userInfo;


HKEY hKey;
HKEY hKey2;

auto subkey_oobe = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OOBE";
auto winlogon = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
auto resultado_oobe = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey_oobe, 0, KEY_WRITE, &hKey2);
auto open_winlogon = RegOpenKeyExA(HKEY_LOCAL_MACHINE, winlogon, 0, KEY_WRITE, &hKey);



void Start(string username, string password)
{
    const char* useroobe = "LaunchUserOOBE";
    USER_INFO_1 userInfo;
    ZeroMemory(&userInfo, sizeof(userInfo));
    userInfo.usri1_name = (LPWSTR)username.c_str();
    userInfo.usri1_password = (LPWSTR)password.c_str();
    userInfo.usri1_priv = USER_PRIV_USER;
    userInfo.usri1_home_dir = NULL;
    userInfo.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD;
    userInfo.usri1_comment = NULL;
    userInfo.usri1_script_path = NULL;
    LOCALGROUP_MEMBERS_INFO_3 account;
    account.lgrmi3_domainandname = (LPWSTR)username.c_str();

    cout << "Creating user\n";

    try {
        NET_API_STATUS status = NetUserAdd(NULL, 1, (LPBYTE)&userInfo, 0);
        status = NetLocalGroupAddMembers(NULL,(LPCWSTR)lang_selected.c_str(), 3, (LPBYTE)&account, 1);
        cout << "User " << username << " created" << " successfully!\n";
    }
    catch (exception ex) {
        cout << &R"(ERROR)";
        cout << ex.what();
        
    }
    

    if (resultado_oobe == ERROR_SUCCESS) {
        RegDeleteValueA(hKey2, useroobe);
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
        cout << "Write your language:\n Available languages:\nENGLISH SPANISH FRENCH GERMAN ITALIAN PORTUGUESE CHINESE JAPANESE RUSSIAN ARABIC HINDI";
        cin >> lang;
        if (lang == NULL)
        {
            lang_selected = ENGLISH;
            cout << "Ignored... Select English by default!\n";

        }
        switch (lang)
        {
        case 1:
            lang_selected = ENGLISH;
            
        case 2:
            lang_selected = SPANISH;
            
        case 3:
            lang_selected = FRENCH;
            
        case 4:
            lang_selected = GERMAN;
            
        case 5:
            lang_selected = ITALIAN;
            
        case 6:
            lang_selected = CHINESE;
            
        case 7:
            lang_selected = RUSSIAN;
            
        case 9:
            lang_selected = JAPANESE;
            
        case 10:
            lang_selected = ARABIC;
            
        case 11:
            lang_selected = HINDI;
            
        default:
            lang_selected = ENGLISH;
            
        }
        
        cout << "Username:";

        cin >> username;
        if (username != "") {
            cout << "Password:";
            cin >> password;
            cin >> lang;
            if (password != "")
            {
                Start(username.c_str(), password.c_str());
            }
            else {
                exit(0);
            }
        }
   }
    