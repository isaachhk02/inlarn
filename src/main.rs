use std::{io, process::{exit, Command, Output}};

use windows_registry::{Key, LOCAL_MACHINE};

extern crate windows_registry;



fn edit_registry(username: &str) {
    let hklm : &Key = LOCAL_MACHINE;
    let open_oobe = hklm.open("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\OOBE");
    if open_oobe.is_ok() {
        println!("Opened registry key successfully!");
        let modify_oobe = hklm.set_string("LaunchUserOOBE", "");
        if modify_oobe.is_ok() {
            println!("Deleted auto-login account installer sucessfully!");
            let _open_winlogon = hklm.open("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon");
            if _open_winlogon.is_ok() {
                println!("Get WinLogon registry path successfully");
                let _set_admin_logon = hklm.set_string("stringAdminLogon", "0");
                if _set_admin_logon.is_ok() {
                    println!("Removed autologin OOBE user!");
                    let _sid = hklm.set_string("stringLogonSID", "0");
                    if _sid.is_ok() {
                        println!("Remove SID Logon");
                        let _changeusername = hklm.set_string("DefaultUserName", username);
                        if _changeusername.is_ok() {
                            println!("Changed default user to {}",username);
                            let _remove_boot_anim = hklm.set_u32("EnableFirstLogonAnimation", 0);
                            if _remove_boot_anim.is_ok() {
                                println!("Removed boot animation screen!");
                                println!("Removing  default user setup account (defaultuser0)");
                                let _remove_default_user: Output = Command::new(r"C:\Windows\System32\net.exe").arg("user").arg("defaultuser0").arg("/DELETE").output().expect("ERROR to remove default user setup installer!");
                                let _rebootpc : Output = Command::new(r"C:\Windows\System32\shutdown.exe").arg("-r").arg("-t").arg("0").output().expect("Error to reboot!");
                                

                            } else {
                                println!("ERROR");
                                exit(-1);
                            }

                        } else {
                            println!("FAIL: Change to new user as default!");
                            exit(-1);
                        }
                    } else {
                        println!("FAILED");
                        exit(-1);
                    }
                } else {
                    println!("FAILED");
                    exit(-1);
                }
            } else {
                println!("FAILED");
                exit(-1);
            }
        } else {
            println!("FAILED");
            exit(-1);
        }
    }
}

fn createuser(username: &str, password: &str,lang:&str) {
    let _selected_lang = String::new();
    if username.is_empty() || password.is_empty() {
        panic!("Cannot create the user without name and password!");
    } else {
        let _create_user = Command::new(r"C:\Windows\System32\net.exe").arg("user").arg(username).arg(password).arg("/ADD").output().expect("Failed to create user!");
        if lang.eq("english") {
            _ = _selected_lang.eq("Administrators");
        if lang.eq("spanish") || lang.eq("portuguese") {
            _ = _selected_lang.eq("Administradores");        
        }
        if lang.eq("german") {
            _ = _selected_lang.eq("Administratoren");        
        }
        if lang.eq("french") {
            _ = _selected_lang.eq("Administrateurs");
        }
        if lang.eq("chinese") {
            _ = _selected_lang.eq("管理员们");
        }
        if lang.eq("japanese") {
            _ = _selected_lang.eq("管理者たち");
        }
        if lang.eq("arab") {
            _ = _selected_lang.eq("مديرين");
        }
        if lang.eq("hindi") {
            _ = _selected_lang.eq("प्रशासकगण");
        }
        let _assign_admin = Command::new(r"C:\Windows\System32\net.exe").arg("localgroup").arg(_selected_lang).arg(username).arg("/ADD").output().expect("Error to assign admin permisions");
        edit_registry(username);
    }
}
}


fn main() {
    let mut _username : String = String::new();
    let mut _password : String = String::new();
    println!("Isaachhk02s Local Account Creator and Microsoft Account requirement bypass");
    println!("Write your language");
    let mut lang = String::new();
    io::stdin().read_line(&mut lang).expect("fail to read!");
    if lang.is_empty() {
        lang = String::from("english");
        println!("No language selected... Using {}",lang);
    } 
    else {
        println!("{}",lang);
        println!("Write your username:");
        _ = io::stdin().read_line(&mut _username);
        if _username.is_empty() {
            println!("No username specified!");
            main()
        } else {
            println!("Write your password:");
            _ = io::stdin().read_line(&mut _password);
            if _password.is_empty() || !_password.is_empty() {
                println!("Your password it's : {}",_password);
                createuser(&_username, &_password,&lang);
            }
            else {
                createuser(&_username, &_password,&lang);
            }
        }
    }
}