use std::process::Command;

pub fn createuser(username: &str, password: &str,lang:&str) {
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
    }
    }
}