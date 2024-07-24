// Created by isaachhk02

#include <windows.h>
#include <winreg.h>
#include <unistd.h>
#include <lm.h>
#include <sddl.h>

#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "advapi32.lib")
#include <stdio.h>

const char *user;
const char *pass;

void CreateUserWithAdminPrivileges(const char *user, const char *pass) {
    USER_INFO_1 ui;
    DWORD dwLevel = 1;
    DWORD dwError = 0;

    ZeroMemory(&ui, sizeof(ui));
    ui.usri1_name = user;
    ui.usri1_password = pass;
    ui.usri1_priv = USER_PRIV_USER;
    ui.usri1_home_dir = NULL;
    ui.usri1_comment = NULL;
    ui.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD;
    ui.usri1_script_path = NULL;

    NET_API_STATUS nStatus = NetUserAdd(NULL, dwLevel, (LPBYTE)&ui, &dwError);

    if (nStatus == NERR_Success) {
        printf("User created successfully!\n");
    } else {
        printf("ERROR: Cannot create the user!\n");
        exit(-1);
        return;
    }
    PSID pSid = NULL;
    DWORD cbSid = 0;
    DWORD cchReferencedDomainName = 0;
    SID_NAME_USE peUse;
    LookupAccountNameW(NULL, user, pSid, &cbSid, NULL, &cchReferencedDomainName, &peUse);

    pSid = (PSID)malloc(cbSid);
    LPWSTR referencedDomainName = (LPWSTR)malloc(cchReferencedDomainName * sizeof(WCHAR));

    if (!LookupAccountNameW(NULL, user, pSid, &cbSid, referencedDomainName, &cchReferencedDomainName, &peUse)) {
        printf("Failed to get SID\n");
        free(pSid);
        free(referencedDomainName);
        return;
    }

    LOCALGROUP_MEMBERS_INFO_0 account;
    account.lgrmi0_sid = pSid;

    nStatus = NetLocalGroupAddMembers(NULL, L"Administrators", 0, (LPBYTE)&account, 1);

    if (nStatus == NERR_Success) {
        printf("User added to admins successfully!\n");
    } else {
        printf("ERROR: Cannot add the user to admin group!\n");
    }

    free(pSid);
    free(referencedDomainName);
}


int ModifyRegistry(const char *user, const char *pass)
{
    // Variables
    HKEY hKey;
    HKEY hKey_two;
    //HKEY hKey_three;
    LONG result;
    LPCSTR subkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OOBE";
    LPCSTR subkey_two = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
    LPCSTR oobekey = "LaunchUserOOBE";
    LPCSTR autologinadmin = "stringAdminLogon";
    LPCSTR loginsid = "stringLogonSID";
    LPCSTR defaultusername = user;
    LPCSTR defaultusername_value_name = "DefaultUserName";
    LPCSTR valueoobe = "";
    LPCSTR firstlogoanimation = "EnableFirstLogonAnimation";
    LPCSTR zero = "0";

    printf("Opening registry key\n");
    result = RegOpenKeyExA(HKEY_LOCAL_MACHINE,subkey,0,KEY_SET_VALUE,&hKey);
    if (result == ERROR_SUCCESS) {
        printf("Opened registry key successfully!\n");
        result = RegSetValueExA(hKey,oobekey,0,REG_SZ,(const BYTE*)valueoobe,0);
        if (result == ERROR_SUCCESS)
            {
                printf("Deleted auto-login account installer sucessfully!\n");
                RegCloseKey(&hKey);
                result = RegOpenKeyExA(HKEY_LOCAL_MACHINE,subkey_two,0,KEY_SET_VALUE,&hKey_two);
                if (result == ERROR_SUCCESS)
                {
                    printf("Opened WinLogon registry path\n");
                    result = RegSetValueExA(hKey_two,autologinadmin,0,REG_SZ,(const BYTE*)zero,0);
                    if (result == ERROR_SUCCESS) {
                        printf("Removed autologin admin\n");
                        result = RegSetValueExA(hKey_two,loginsid,0,REG_SZ,(const BYTE*)zero,0);
                        if (result == ERROR_SUCCESS)
                        {
                            printf("Removed other things with relation for bypass the user setup wizard!\n");
                            printf("Changing the username to %s",&user);
                            printf("\n");
                            result = RegSetValueExA(hKey_two,defaultusername_value_name,0,REG_SZ,(const BYTE*)user,0);
                            if (result == ERROR_SUCCESS)
                            {
                                printf("Changed successfully!\n");
                                result = RegSetValueExA(hKey_two,firstlogoanimation,0,REG_DWORD,(const BYTE*)0,0);
                                if (result == ERROR_SUCCESS) {
                                        printf("Disabled First login animation/screen!\n");
                                } else {
                                    printf("ERROR: Cannot disable the animation or screen of first logon! Continue....");
                                }
                                printf("Done!\n");
                                exit(1);

                            } else {
                                printf("ERROR: Cannot change to username\n");
                                exit(-1);
                            }

                        }
                    }
                }
                else {
                    printf("ERROR: To open the registry key!\n");
                    exit(-1);
                }
            }
    }
    return 0;
}


int main(int argc, const char** argv)
{
    if (argv[1] != NULL)
    {
        printf("Not enough args\n");
        if (argv[2] != NULL)
        {
            user = argv[1];
            pass = argv[2];

            CreateUserWithAdminPrivileges(user,pass);
            ModifyRegistry(user,pass);
        }
    } else {
        printf("inlarn.exe [user] [pass]\n");
    }

    return 0;
}
