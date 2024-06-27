# Created by hhk02 (isaachhk02)
import subprocess
import sys
import winreg
import os
import win32api
import time
from win32api import *


zero = int(0)
nada = None
username = None
password = None
lang = "english"
hrootMachine = winreg.HKEY_LOCAL_MACHINE

def ChangeRegistries():
    open_key = winreg.OpenKey(hrootMachine,"/SOFTWARE/Microsoft/Windows/CurrentVersion/OOBE")
    remove_oobe = winreg.DeleteValue(hrootMachine,"/SOFTWARE/Microsoft/Windows/CurrentVersion/OOBE","LaunchUserOOBE")
    open_winlogon = winreg.OpenKey(hrootMachine,"/SOFTWARE/Microsoft/Windows NT/CurrentVersion/Winlogon")
    adminlogon = winreg.SetValue(hrootMachine,"/SOFTWARE/Microsoft/Windows NT/CurrentVersion/Winlogon/AutoAdminLogon",winreg.REG_SZ,"0")
    autologin = winreg.SetValue(hrootMachine,"/SOFTWARE/Microsoft/Windows NT/CurrentVersion/Winlogon/AutoLogonSID",winreg.REG_SZ,"")
    dusername = winreg.SetValue(hrootMachine,"/SOFTWARE/Microsoft/Windows NT/CurrentVersion/Winlogon/DefaultUserName",winreg.REG_SZ,"")
    enablefba = winreg.SetValue(hrootMachine,"/SOFTWARE/Microsoft/Windows NT/CurrentVersion/Winlogon/EnableFirstLogonAnimation",winreg.REG_DWORD,0)
    if open_key:
        print("First registry path has opened!")
        if remove_oobe:
            print("Removed the user setup on startup!")
            if open_winlogon:
                print("Opened HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon successfully!")
                if adminlogon:
                    print("Value changed!")
                    if autologin:
                        print("Value changed!")
                        if dusername:
                            print("Value changed!")
                            if enablefba:
                                print("Value changed!")
                                print("Done! please reboot the system press any key to restart!")
                                os.system("shutdown.exe -r -t 0")
            else:
                print("ERROR")
        else:
            print("Error: cannot open registry key path!")
    else:
        print("Failed opening the first registry key!")
        sys.exit(-1)


def CreateUser(username: str, password: str):
    print("Creating user...")
    os.system("net user " + username + " " + password + " /add")
    if lang == "spanish" or "SPANISH" or "Spanish":
        os.system("net localgroup administradores " + username + " /add")
        ChangeRegistries()
    if lang == "english" or "ENGLISH" or "English":
        os.system("net localgroup administrators " + username + " /add")
        ChangeRegistries()
def start():
    print("isaachhk02's Local Account Creator and Microsoft Account requirement bypass")
    i = input("Press any key to start")
    lang = input("What it's your system language ex: spanish?")
    if lang == "spanish" or "SPANISH" or "Spanish":
        lang = "spanish"
    else:
        lang = "english"
    username = input("Username:")
    if username != None:
        if password != None:
            CreateUser(username,password)
        else:
            start()
        pass
    pass
pass
start()