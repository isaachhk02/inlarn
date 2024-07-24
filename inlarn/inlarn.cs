using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.DirectoryServices.AccountManagement;
using System.Linq;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace inlarn
{
    public class inlarn
    {
        public static string user = Environment.GetCommandLineArgs()[1];
        public static string pass = Environment.GetCommandLineArgs()[2];
        string OOBE_SUBKEY = @"SOFTWARE\Microsoft\Windows\CurrentVersion\OOBE";
        string WINLOGON_SUBKEY = @"SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon";
        string OOBE_KEY = "LaunchUserOOBE";
        string AUTOLOGINADMIN = "stringAdminLogon";
        string LOGINSID = "stringLogonSID";
        string DEFAULTUSER = user;
        string DEFAULTUSERNAMEKEY = "DefaultUserName";
        string ZERO = "0";
        string FIRSTLOGOANIM = "EnableFirstLogonAnimation";

        void PatchRegistry(string username)
        {
            try
            {
                Registry.SetValue("HKEY_LOCAL_MACHINE\\" + OOBE_SUBKEY, OOBE_KEY, "");
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("Bypassed OOBE Setup (User Setup Wizard)");
                Registry.SetValue("HKEY_LOCAL_MACHINE\\" + WINLOGON_SUBKEY, AUTOLOGINADMIN, ZERO);
                Console.WriteLine("Disabled auto-login admin account!");
                Registry.SetValue("HKEY_LOCAL_MACHINE\\" + WINLOGON_SUBKEY, LOGINSID, ZERO);
                Registry.SetValue("HKEY_LOCAL_MACHINE\\" + WINLOGON_SUBKEY, DEFAULTUSERNAMEKEY, DEFAULTUSER);

                Console.WriteLine("Username set to " + DEFAULTUSER);


                Registry.SetValue("HKEY_LOCAL_MACHINE\\" + WINLOGON_SUBKEY, FIRSTLOGOANIM, 0);
                Console.WriteLine("Disabled First Boot Screen Screen!");


            }
            catch (Exception ex) { Console.WriteLine(ex.ToString()); };


        }

        public void Start()
        {
            
                CreateUser(user, pass);
                PatchRegistry(user);
        }

        private void CreateUser(string user, string pass)
        {
            UserPrincipal principal = new UserPrincipal(new PrincipalContext(ContextType.Machine));

            Console.WriteLine("Creating user!");
            try
            {
                principal.Name = user;
                principal.PasswordNeverExpires = true;
                principal.SetPassword(pass);
                principal.Description = "";
                principal.DisplayName = user;
                principal.UserCannotChangePassword = false;
                principal.Save();

                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("Adding to Admin group!");
                GroupPrincipal group = GroupPrincipal.FindByIdentity(principal.Context, "Administrators");
                group.Members.Add(principal);
                group.Save();

                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("Created all successfully!");
            }
            catch (Exception ex) { Console.ForegroundColor = ConsoleColor.DarkRed; Console.WriteLine(ex.Message); };
        }
    }
}
