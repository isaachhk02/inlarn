# Created by hhk02 (isaachhk02)
import winreg
import os

zero = int(0)
nada = None
username = None
password = None
hrootMachine = winreg.HKEY_LOCAL_MACHINE

def CreateUser(username: str, password: str):
    print("Creating user...")
    

def start():
    print("isaachhk02's Local Account Creator and Microsoft Account requirement bypass")
    i = input("Press any key to start")
    username = input("Username:")
    if username != None:
        if password != None:
            CreateUser(username,password)
        else:
            start()
        pass
    pass
pass