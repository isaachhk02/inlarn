// created by isaachhk02 (isaacfhl)

#include <iostream>
#include <windows.h>
#include <winreg.h>

#include "inlarn.h"
#include <lm.h>

#pragma comment(lib, "netapi32.lib")
using namespace std;
USER_INFO_1 userInfo;
string username;
string password;
string group;
string lang;
LPCWSTR lang_selected;



HKEY hKey;
HKEY hKey2;

auto subkey_oobe = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OOBE";
auto winlogon = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
auto resultado_oobe = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey_oobe, 0, KEY_WRITE, &hKey2);
auto open_winlogon = RegOpenKeyExA(HKEY_LOCAL_MACHINE, winlogon, 0, KEY_WRITE, &hKey);

void PatchRegistry()
{
    const char* useroobe = "LaunchUserOOBE";
   
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

void CreateUser(string username, string password) {
    
    userInfo.usri1_name = (LPWSTR)username.c_str();
    userInfo.usri1_password = (LPWSTR)password.c_str();
    userInfo.usri1_priv = USER_PRIV_USER;
    userInfo.usri1_home_dir = NULL;
    userInfo.usri1_comment = NULL;
    userInfo.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD;
    userInfo.usri1_script_path = NULL;
    LOCALGROUP_MEMBERS_INFO_3 account;
    account.lgrmi3_domainandname = (LPWSTR)username.c_str();
    cout << "Creating user\n";
    
    

    
    NET_API_STATUS status = NetUserAdd(NULL, 1, (LPBYTE)&userInfo, 0);
    if (lang == "english")
        status = NetLocalGroupAddMembers(NULL,L"Administrators",3,(LPBYTE)&account, 1);
    if (lang == "german")
        status = NetLocalGroupAddMembers(NULL,L"Administratoren",3,(LPBYTE)&account, 1);
    if (lang == "french")
        status = NetLocalGroupAddMembers(NULL,L"Administrateurs",3,(LPBYTE)&account, 1);
    if (lang == "spanish" || lang == "portuguese")
        status = NetLocalGroupAddMembers(NULL,L"Administradores",3,(LPBYTE)&account, 1);
    if (lang == "italian")
        status = NetLocalGroupAddMembers(NULL,L"Amministratori",3,(LPBYTE)&account, 1);
    if (lang == "chinese")
        status = NetLocalGroupAddMembers(NULL,L"管理员们",3,(LPBYTE)&account, 1);
    if (lang == "japanese")
        status = NetLocalGroupAddMembers(NULL,L"管理者たち",3,(LPBYTE)&account, 1);
    if (lang == "russian")
        status = NetLocalGroupAddMembers(NULL,L"Администраторы",3,(LPBYTE)&account, 1);
    if (lang == "arabic")
        status = NetLocalGroupAddMembers(NULL,L"مديرين",3,(LPBYTE)&account, 1);
    if (lang == "hindi")
        status = NetLocalGroupAddMembers(NULL,L"प्रशासकगण",3,(LPBYTE)&account, 1);
    if (status == NERR_Success) {
        cout << "User " << username.c_str() << " created" << " successfully!\n";
        PatchRegistry();
    } else {
        cout << "Error!";
    }
    
    

}

int main()
{
    std::cout << "isaachhk02s Local Account Creator and Microsoft Account requirement bypass\n";
    system("pause");
    cout << "Write your language:\n Available languages:\nENGLISH SPANISH FRENCH GERMAN ITALIAN PORTUGUESE CHINESE JAPANESE RUSSIAN ARABIC HINDI\n";
    
    cin >> lang;
        
        
        
    cout << "Username:";

    cin >> username;
    if (username != "") {
        cout << "Password:";
        cin >> password;
        cin >> lang;
        if (password == "")
        {
            password = "";
            CreateUser(username.c_str(),password.c_str());
        } 
        else {
            CreateUser(username.c_str(),password.c_str());
        }
    }
}
    