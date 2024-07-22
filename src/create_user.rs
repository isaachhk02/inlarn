use windows::core::PCWSTR;
use windows::Win32::Security::{ConvertStringSidToSidW, PSID};
use windows::Win32::System::Memory::LocalFree;
use windows::Win32::Foundation::ERROR_SUCCESS;
use netuser_rs::{NetUser, NetGroup};

fn to_pcwstr(s: &str) -> PCWSTR {
    PCWSTR(std::ffi::OsStr::new(s)
        .encode_wide()
        .chain(Some(0).into_iter())
        .collect::<Vec<u16>>()
        .as_ptr())
}

pub fn create_user(user: &str, pass: &str) {
    // Step 1: Create the user
    let username = user;
    let password = pass;

    match NetUser::add(username, password) {
        Ok(_) => println!("User created successfully."),
        Err(err) => {
            eprintln!("Failed to create user: {}", err);
            return;
        }
    }

    // Step 2: Add the user to the "Administrators" group using SID
    unsafe {
        let admin_sid_str = to_pcwstr("S-1-5-32-544");
        let mut admin_sid: PSID = std::ptr::null_mut();
        let sid_result = ConvertStringSidToSidW(admin_sid_str, &mut admin_sid);

        if sid_result.as_bool() {
            let admin_group_name = "Administrators";

            match NetGroup::add_user(admin_group_name, username) {
                Ok(_) => println!("User added to the Administrators group successfully."),
                Err(err) => eprintln!("Failed to add user to the Administrators group: {}", err),
            }

            LocalFree(admin_sid as *mut _);
        } else {
            eprintln!("Failed to convert SID string to SID.");
        }
    }
}
