mod createuser;
mod registry;

use std::{io, process::{exit, Command, Output}};

use windows_registry::{Key, LOCAL_MACHINE};

extern crate windows_registry;

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
                edit_registry(&_username);
            }
            else {
                createuser(&_username, &_password,&lang);
                edit_registry(&_username);
            }
        }
    }
}