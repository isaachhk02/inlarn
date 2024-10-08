﻿using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics.Eventing.Reader;
using System.DirectoryServices.AccountManagement;
using System.Linq;
using System.Security.Permissions;
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
        string AUTOLOGINADMIN = "AutoAdminLogon";
        string LOGINSID = "AutoLogonSID";
        string DEFAULTUSERNAMEKEY = "DefaultUserName";
        string ZERO = "0";
        string FIRSTLOGOANIM = "EnableFirstLogonAnimation";

        void PatchRegistry(string username)
        {
            try
            {
                RegistryKey HKLM = Registry.LocalMachine;
                HKLM.OpenSubKey(OOBE_SUBKEY);
                HKLM.DeleteValue("LaunchUserOOBE", true);
                HKLM.Close();
               
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("Bypassed OOBE Setup (User Setup Wizard)");
                HKLM.OpenSubKey(WINLOGON_SUBKEY);
                HKLM.SetValue(AUTOLOGINADMIN, ZERO);
                Console.WriteLine("Disabled auto-login admin account!");
                HKLM.SetValue(LOGINSID, "");
                HKLM.SetValue(DEFAULTUSERNAMEKEY, user);
                HKLM.SetValue(FIRSTLOGOANIM, 0);
                Console.WriteLine("Disabled First Boot Screen Screen!");
                HKLM.Close();

            }
            catch (Exception ex) { Console.WriteLine(ex.ToString()); };


        }

        public void Start()
        {
            if (pass == "")
            {
                CreateUser(user, "");
            } else
            {
                CreateUser(user, pass);
            }
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
                var identifier = new SecurityIdentifier(WellKnownSidType.BuiltinAdministratorsSid, null);
                var role = identifier.Translate(typeof(NTAccount)).Value;
                GroupPrincipal group = GroupPrincipal.FindByIdentity(principal.Context, role);
                group.Members.Add(principal);
                group.Save();

                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("Created all successfully!");

                Console.WriteLine("Removing defaultuser0");
                PrincipalContext ctx = new PrincipalContext(ContextType.Machine);
                UserPrincipal usrp = new UserPrincipal(ctx);
                usrp.Name = "defaultuser0";
                PrincipalSearcher ps_usr = new PrincipalSearcher(usrp);
                var u = ps_usr.FindOne();
                u.Delete();
               

            }
            catch (Exception ex) { Console.ForegroundColor = ConsoleColor.DarkRed; Console.WriteLine(ex.Message); };
        }
    }
}
