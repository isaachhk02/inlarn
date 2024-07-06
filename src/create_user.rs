
#[cfg(windows)] extern crate winapi;
extern crate widestring;

#[cfg(windows)]
pub fn createuser(_username : &str, _password: &str, _language: &str) {
    use std::ptr::null_mut;
    use widestring::U16CString;
    use winapi::shared::lmcons::NET_API_STATUS;
    use winapi::um::lmaccess::{NetUserAdd, NetLocalGroupAddMembers, USER_INFO_1, LOCALGROUP_MEMBERS_INFO_3, USER_PRIV_USER};

    unsafe {
        // Define the user details
        let username = U16CString::from_str(_username).unwrap();
        let password = U16CString::from_str(_password).unwrap();

        // Prepare USER_INFO_1 structure
        let user_info = USER_INFO_1 {
            usri1_name: username.as_ptr() as *mut _,
            usri1_password: password.as_ptr() as *mut _,
            usri1_priv: USER_PRIV_USER,
            usri1_home_dir: null_mut(),
            usri1_comment: null_mut(),
            usri1_flags: 0x0001, // UF_SCRIPT
            usri1_script_path: null_mut(),
            usri1_password_age: 0x0001,
        };

        let mut parm_err: u32 = 0;

        // Add the user
        let status: NET_API_STATUS = NetUserAdd(null_mut(), 1, &user_info as *const _ as *mut _, &mut parm_err);
        if status == 0u32 {
            println!("User created successfully");

            // Add the user to the Administrators group
            let group_name = U16CString::from_str(_language).unwrap();
            let member_info = LOCALGROUP_MEMBERS_INFO_3 {
                lgrmi3_domainandname: username.as_ptr() as *mut _,
            };

            let status: NET_API_STATUS = NetLocalGroupAddMembers(
                null_mut(),
                group_name.as_ptr(),
                3,
                &member_info as *const _ as *mut _,
                1,
            );

            if status == 0u32 {
                println!("User added to Administrators group successfully");
            } else {
                println!("Failed to add user to Administrators group, error code: {}", status);
            }
        } else {
            println!("Failed to create user, error code: {}", status);
        }
    }

}
