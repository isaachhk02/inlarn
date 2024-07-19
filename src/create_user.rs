
#[cfg(windows)] extern crate netuser_rs;

#[cfg(windows)]
pub fn createuser(_username : &str, _password: &str) {
    if let Err(err) = netuser_rs::users::add_user(_username, _password, &None) {
        println!("Error: {} - {}\n", err, netuser_rs::win_err_text(err));
        return;
    } else {
        println!("Account created successfully!");
        println!("Adding to Admin Group!");
        if let Err(errtwo) = netuser_rs::groups::add_user_to_group(_username,"Administrators") {
            println!("Error {} - {}\n", errtwo, netuser_rs::win_err_text(errtwo));
            return;
        }
        return;
    }
}