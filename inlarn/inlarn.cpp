// created by isaachhk02 (isaacfhl)

#include <iostream>
#include <windows.h>
#include <winreg.h>
#include <process.h>
#include "inlarn.h"
#include <unistd.h>

using namespace std;

string username;
string password;

string lang;

HKEY hKey;
HKEY hKey2;

auto subkey_oobe = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OOBE";
auto winlogon = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
auto resultado_oobe = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey_oobe, 0, KEY_WRITE, &hKey2);
auto open_winlogon = RegOpenKeyExA(HKEY_LOCAL_MACHINE, winlogon, 0, KEY_WRITE, &hKey);


void CreateUser(string username, string password) {
    cout << "Creating user\n";
    execl("C:\\Windows\\System32\\net.exe",["user",username,password,"/add"]);

    
    if (lang == "english")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","Administrators",username,"/add"]);
    if (lang == "german")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","Administratoren",username,"/add"]);
    if (lang == "french")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","Administrateurs",username,"/add"]);
    if (lang == "spanish" || lang == "portuguese")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","Administradores",username,"/add"]);
    if (lang == "italian")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","Amministratori",username,"/add"]);
    if (lang == "chinese")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","管理员们",username,"/add"]);
    if (lang == "japanese")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","管理者たち",username,"/add"]);
        
    if (lang == "russian")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","Администраторы",username,"/add"]);
    if (lang == "arabic")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","مديرين",username,"/add"]);
    if (lang == "hindi")
        execl("C:\\Windows\\System32\\net.exe",["localgroup","प्रशासकगण",username,"/add"]);
    if (status == 0) {
        cout << "User " << username.c_str() << " created" << " successfully!\n";
    } else {
        cout << "Error!";
    }
    
    

}
void PatchRegistry()
{
    const char* useroobe = "LaunchUserOOBE";
    cout << "Patching\n";
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
            PatchRegistry();
            
            
        } 
        else {
            CreateUser(username.c_str(),password.c_str());
            PatchRegistry();
            
        }
    }
}
    