
#[cfg(windows)] extern crate winapi;

#[cfg(windows)]

use std::ptr;
use std::ffi::OsStr;
use std::os::windows::ffi::OsStrExt;
use winapi::um::lmaccess::{NetUserAdd, USER_INFO_1, UF_SCRIPT, NetLocalGroupAddMembers, LOCALGROUP_MEMBERS_INFO_0};
use winapi::um::lmapibuf::NetApiBufferFree;
use winapi::um::winnt::{LPCWSTR, WCHAR, PSID};
use winapi::um::sddl::ConvertStringSidToSidW;
use winapi::um::winerror::ERROR_SUCCESS;


fn to_lpcwstr(s: &str) -> *const WCHAR {
    OsStr::new(s)
        .encode_wide()
        .chain(Some(0).into_iter())
        .collect::<Vec<u16>>()
        .as_ptr()
}

pub fn createuser(_username : &str, _password: &str) {
    unsafe {
        let username = to_lpcwstr(_username);
        let password = to_lpcwstr(_password);

        // Step 1: Create the user
        let mut user_info = USER_INFO_1 {
            usri1_name: username as LPCWSTR,
            usri1_password: password as LPCWSTR,
            usri1_password_age: 0,
            usri1_priv: 1,
            usri1_home_dir: ptr::null_mut(),
            usri1_comment: ptr::null_mut(),
            usri1_flags: UF_SCRIPT,
            usri1_script_path: ptr::null_mut(),
        };

        let mut parm_err: u32 = 0;
        let result = NetUserAdd(
            ptr::null_mut(),
            1,
            &mut user_info as *mut USER_INFO_1 as *mut _,
            &mut parm_err,
        );

        if result == ERROR_SUCCESS {
            println!("User created successfully.");

            // Step 2: Add the user to the "Administrators" group using SID
            let admin_sid_str = to_lpcwstr("S-1-5-32-544");
            let mut admin_sid: PSID = ptr::null_mut();
            let sid_result = ConvertStringSidToSidW(admin_sid_str, &mut admin_sid);

            if sid_result != 0 {
                let mut local_group_members = LOCALGROUP_MEMBERS_INFO_0 {
                    lgrmi0_sid: admin_sid,
                };

                let result = NetLocalGroupAddMembers(
                    ptr::null_mut(),
                    admin_sid_str,
                    0,
                    &mut local_group_members as *mut LOCALGROUP_MEMBERS_INFO_0 as *mut _,
                    1,
                );

                if result == ERROR_SUCCESS {
                    println!("User added to the Administrators group successfully.");
                } else {
                    println!("Failed to add user to the Administrators group. Error code: {}", result);
                }
            } else {
                println!("Failed to convert SID string to SID.");
            }
        } else {
            println!("Failed to create user. Error code: {}", result);
        }

        // Free any allocated buffers (if applicable)
        NetApiBufferFree(user_info.usri1_name as *mut _);
        NetApiBufferFree(user_info.usri1_password as *mut _);
    }
}