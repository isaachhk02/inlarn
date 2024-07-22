#[cfg(windows)]
pub fn edit_registry(username: &str) {
    use std::process::exit;
    use windows_registry::{Key, LOCAL_MACHINE};
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
                                //let _rebootpc : Output = Command::new(r"C:\Windows\System32\shutdown.exe").arg("-r").arg("-t").arg("0").output().expect("Error to reboot!");
                                

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