// created by isaachhk02 (isaacfhl)

#include <iostream>
#include <windows.h>
#include <winreg.h>
#include "inlarn.h"
#include <unistd.h>

using namespace std;

const char *username;
const char *password;

const char *user_add;

const char *english;

const char *german;

const char *french;

const char *spanish_portuguese;

const char *italian;

const char *chinese;


const char *japanese;

const char *russian;

const char *arab;

const char *hindi;

char *lang;

HKEY hKey;
HKEY hKey2;

auto subkey_oobe = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OOBE";
auto winlogon = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
auto resultado_oobe = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey_oobe, 0, KEY_WRITE, &hKey2);
auto open_winlogon = RegOpenKeyExA(HKEY_LOCAL_MACHINE, winlogon, 0, KEY_WRITE, &hKey);


void CreateUser() {
    user_add = "user " , username  , password , "/add";

    english = "localgroup Administrators " , username , "/add";

    german = "localgroup Administratoren " , username , "/add";

    french = "localgroup  Administrateurs " , username , "/add";

    spanish_portuguese = "localgroup Administradores ",username,"/add";

    italian = "localgroup Amministratori " , username , "/add";

    chinese = "localgroup 管理员们 ",username, " /add";


    japanese = "localgroup 管理者たち " , username , "/add";

    russian = "localgroup Администраторы " , username , "/add";

    arab = "localgroup مديرين " , username , "/add";

    hindi  = "localgroup प्रशासकगण " , username , "/add";
    printf("%s","Creating user....");
    execl("C:\\Windows\\System32\\net.exe",user_add);

    
    if (lang == "english")
        execl("C:\\Windows\\System32\\net.exe",english);
    if (lang == "german")
        execl("C:\\Windows\\System32\\net.exe",german);
    if (lang == "french")
        execl("C:\\Windows\\System32\\net.exe",french);
    if (lang == "spanish" || lang == "portuguese")
        execl("C:\\Windows\\System32\\net.exe",spanish_portuguese);
    if (lang == "italian")
        execl("C:\\Windows\\System32\\net.exe",italian);
    if (lang == "chinese")
        execl("C:\\Windows\\System32\\net.exe",chinese);
    if (lang == "japanese")
        execl("C:\\Windows\\System32\\net.exe",japanese);
        
    if (lang == "russian")
        execl("C:\\Windows\\System32\\net.exe",russian);
    if (lang == "arabic")
        execl("C:\\Windows\\System32\\net.exe",arab);
    if (lang == "hindi")
        execl("C:\\Windows\\System32\\net.exe",hindi);
    printf("%s","User created successfully!\n");
    
    
    

}
void PatchRegistry()
{
    const char* useroobe = "LaunchUserOOBE";
    cout << "Patching\n";
    if (resultado_oobe == ERROR_SUCCESS) {
        RegDeleteValueA(hKey2,useroobe);
    }
    if (open_winlogon == ERROR_SUCCESS) {
        RegSetValueExA(hKey,"stringAdminLogon", 0, REG_SZ, (const BYTE*)"0",0);
        RegSetValueExA(hKey,"stringLogonSID", 0, REG_SZ, (const BYTE*)"", 0);
        RegSetValueExA(hKey,"DefaultUserName", 0, REG_SZ, (const BYTE*)"", 0);
        RegSetValueExA(hKey,"EnableFirstLogonAnimation", 0, REG_DWORD, (const BYTE*)(0), 0);

        printf("%s","All done!\n");
        RegCloseKey(hKey);
    }
    else {
        printf("%s","ERROR\n");
    }
}
int main()
{
    printf("%s","isaachhk02s Local Account Creator and Microsoft Account requirement bypass\n");
    getchar();
    printf("%s","Write your language:\n");
    
    scanf("%s",lang);
        
        
        
    printf("%s","Write your username:");

    scanf("%s",username);
    if (username != "") {
        printf("%s","Write your password:");
        scanf("%s",password);
        scanf("%s",lang);
        if (password == "")
        {
            password = "";
            CreateUser();
            PatchRegistry();
            
            
        } 
        else {
            CreateUser();
            PatchRegistry();
            
        }
    }
}
    