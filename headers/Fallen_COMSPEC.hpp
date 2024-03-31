#ifndef FALLEN_COMSPEC_HPP
#define FALLEN_COMSPEC_HPP
#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <color.hpp>
using namespace std;
namespace conhost
{
    string Install_DIR = filesystem::current_path().string();
    size_t Split(const string &txt, vector<string> &strs, char ch)
    {
        size_t pos = txt.find( ch );
        size_t initialPos = 0;
        strs.clear();
        while( pos != string::npos ) {
            strs.push_back( txt.substr( initialPos, pos - initialPos ) );
            initialPos = pos + 1;

            pos = txt.find( ch, initialPos );
        }
        strs.push_back( txt.substr( initialPos, min( pos, txt.size() ) - initialPos + 1 ) );

        return strs.size();
    }
    string ConvertToUppercase(string Input){
        string ToReturn = Input;
        transform(ToReturn.begin(), ToReturn.end(), ToReturn.begin(), ::toupper);
        return ToReturn;
    };
    string ConvertToLowercase(string Input){
        string ToReturn;
        transform(ToReturn.begin(), ToReturn.end(), ToReturn.begin(), ::tolower);
        return ToReturn;
    };
    string Remove_SUBSTR(string Text,string Substring){
        size_t Index = Text.find(Substring);
        string Operand = Text;
        if (Index != string::npos){
            Operand.erase(Index,(Substring.length()));
        }else{
            cout << dye::red("[-] ") + dye::light_aqua("Runtime ERR in [incl\\Fallen_COMSPEC.hpp] at ns(conhost):Remove_SUBSTR");
        }
        return Operand;
    }
    class Shell{
        private:
            void CReadFile(string filename,int Is_Special_File){
                ifstream file;
                string Content;
                string EndCommand = "del " + filename;
                switch (Is_Special_File){
                    case 0:
                        file.open(filename);
                        while (getline(file,Content)){
                            cout << dye::blue("[*] ") + dye::aqua(Content) + "\n";
                        }
                        file.close();
                        system(EndCommand.c_str());
                        break;
                    case 1:
                        file.open(filename);
                        while (getline(file,Content)){
                            if(filesystem::is_directory(Content)){
                                cout << dye::green(Content) + dye::light_blue(" -> ") + dye::green("DIR \n");
                            }
                            if (filesystem::is_regular_file(Content) && Content != filename){
                                cout << dye::white(Content) + dye::light_blue(" -> ") + dye::white("FILE \n");
                            }
                        }
                        file.close();
                        system(EndCommand.c_str());
                        break;
                    case 2:
                        file.open(filename);
                        while (getline(file,Content)){
                            if (strstr(Content.c_str(),"[STRING] ")){
                                string ARG_NAME = Remove_SUBSTR(Content,"[STRING] ");
                                cout << dye::green("Argument Type : ") + dye::white("String ") + dye::aqua(ARG_NAME + "\n");
                            }
                            if (strstr(Content.c_str(),"[SWITCH] ")){
                                string ARG_NAME = Remove_SUBSTR(Content,"[SWITCH] ");
                                cout << dye::green("Argument Type : ") + dye::white("Switch ") + dye::aqua(ARG_NAME + "\n");
                            }
                            if (strstr(Content.c_str(),"[INT] ")){
                                string ARG_NAME = Remove_SUBSTR(Content,"[INT] ");
                                cout << dye::green("Argument Type : ") + dye::white("Integer ") + dye::aqua(ARG_NAME + "\n");
                            }
                            if (strstr(Content.c_str(),"[BOOLEAN] ")){
                                string ARG_NAME = Remove_SUBSTR(Content,"[BOOLEAN] ");
                                cout << dye::green("Argument Type : ") + dye::white("1-Bit / Boolean ") + dye::aqua(ARG_NAME + "\n");
                            }
                            if (Content[0] == '#'){
                                string Description = Remove_SUBSTR(Content,"#");
                                cout << dye::light_green(" |") + dye::aqua(Description + "\n");
                            }
                        }
                        break;
                    default:
                        cout << dye::red("[-] ") + dye::light_blue("Runtime ERR in [incl\\Fallen_COMSPEC.hpp] at class(Shell):meth(CReadFile)\nInstall DIR: " + Install_DIR + "\n");
                }
            }
        public:
            string FULL_EXECUTION_PATH = filesystem::current_path().string();
            string ConsoleType;
            void Eval(string Command){
                const char *CppCommand = Command.c_str();
                system(CppCommand);
            };
            void NetUtils(vector<string> argv){
                for (int i = 1; i < argv.size(); i++){
                    if (argv[i] == "/Check:InternetConnectivity"){
                        system("ping google.com > NetUtils.log");
                        ifstream file;
                        string Content;
                        file.open("NetUtils.log");
                        while (getline(file,Content)){
                            if (Content == "Ping request could not find host google.com. Please check the name and try again."){
                                cout << dye::red("[-] ") + dye::blue("NetUtils: Internet Connection Is Unavailable.\n");
                                break;
                            }else{
                                cout << dye::green("[+] ") + dye::blue("NetUtils: Internet Connection Is Available.\n");
                                break;
                            }
                        }
                        file.close();
                        system("del NetUtils.log");
                    }else if (argv[i] == "/Show:Configuration"){
                        system("ipconfig > NetUtils.log");
                        CReadFile("NetUtils.log",0);
                        break;
                    }else if (argv[i] == "/Show:AdvancedConfiguration"){
                        system("ipconfig /allcompartments /all > NetUtils.log");
                        CReadFile("NetUtils.log",0);
                        break;
                    }else if (argv[i] == "/Administrative" and argv[i + 1] == "/Configuration:Reset"){
                        system("ipconfig /flushdns > NetUtils.log");
                        CReadFile("NetUtils.log",0);
                        system("ipconfig /registerdns > NetUtils.log");
                        CReadFile("NetUtils.log",0);
                        system("ipconfig /release > NetUtils.log");
                        CReadFile("NetUtils.log",0);
                        system("ipconfig /renew > NetUtils.log");
                        CReadFile("NetUtils.log",0);
                        system("netsh int ip reset > NetUtils.log");
                        CReadFile("NetUtils.log",0);
                        system("netsh winsock reset > NetUtils.log");
                        CReadFile("NetUtils.log",0);
                        break;
                    }else{
                        cout << dye::red("[-] ") + dye::blue("NetUtils: Unknown Argument.\n");
                        break;
                    };
                };
            }
            void AutoComplete(string DOS_CMD){
                string DOS_DIC[] = {
                    "ARP",
                    "AUDITPOL"
                    "ASSOC",
                    "ATTRIB",
                    "BREAK",
                    "BCDEDIT",
                    "BCDBOOT",
                    "BDEHDCFG",
                    "BOOTSECT",
                    "CACLS",
                    "CALL",
                    "CD",
                    "CHCP",
                    "CERTREQ",
                    "CERTUTIL",
                    "CHANGE",
                    "CHCP",
                    "CHDIR",
                    "CHECKNETISOLATION",
                    "CHGPORT",
                    "CHKDSK",
                    "CHKNTFS",
                    "CHGUSR",
                    "CHOICE",
                    "CIPHER",
                    "CLIP",
                    "CMDKEY",
                    "CMSTP",
                    "CSCRIPT",
                    "CLS",
                    "CMD",
                    "COLOR",
                    "COMP",
                    "COMPACT",
                    "CONVERT",
                    "COPY",
                    "DATE",
                    "DEL",
                    "DIR",
                    "DBLSPACE",
                    "DEFRAG",
                    "DISKPERF",
                    "DISKRAID",
                    "DISM",
                    "DISPDIAG",
                    "DJOIN",
                    "DRVSPACE",
                    "DISKPART",
                    "DOSKEY",
                    "DRIVERQUERY",
                    "ECHO",
                    "ENDLOCAL",
                    "ERASE",
                    "EXIT",
                    "ESENTUTL",
                    "FC",
                    "FDISK",
                    "FIND",
                    "FINDSTR",
                    "FINGER",
                    "FLTMC",
                    "FONDUE",
                    "FOR",
                    "FORFILES",
                    "FORMAT",
                    "FSUTIL",
                    "FTP",
                    "FTYPE",
                    "GETMAC",
                    "GOTO",
                    "GPRESULT",
                    "GPUPDATE",
                    "HELP",
                    "HOSTNAME",
                    "ICACLS",
                    "IF",
                    "IPCONFIG",
                    "IPXROUTE",
                    "ISCSICLI",
                    "KLIST",
                    "KSETUP",
                    "KTMUTIL",
                    "LABEL",
                    "LICENSINGDIAG",
                    "LODCTR",
                    "LOGMAN",
                    "LOGOFF",
                    "MANAGE-BDE",
                    "MD",
                    "MEM",
                    "MKDIR",
                    "MOVE",
                    "MKLINK",
                    "MODE",
                    "MOFCOMP",
                    "MORE",
                    "MOUNTVOL",
                    "MRINFO",
                    "MSG",
                    "MSIEXEC",
                    "NET",
                    "NETSH",
                    "NETSTAT",
                    "NETUTILS",
                    "PATH",
                    "PATHPING",
                    "PAUSE",
                    "PING",
                    "PKGMGR",
                    "PUSHD",
                    "POPD",
                    "POWERCFG",
                    "PRINT",
                    "PROMPT",
                    "QUERY",
                    "QUSER",
                    "RD",
                    "RMDIR",
                    "RECOVER",
                    "REG",
                    "REGINI",
                    "REM",
                    "REN",
                    "RENAME",
                    "REPAIR-BDE",
                    "REPLACE",
                    "RESET",
                    "ROBOCOPY",
                    "ROUTE",
                    "RUNAS",
                    "SC",
                    "SCHTASKS",
                    "SET",
                    "SETLOCAL",
                    "SFC",
                    "SHIFT",
                    "SHUTDOWN",
                    "SORT",
                    "START",
                    "SYSTEMINFO",
                    "TAKEOWN",
                    "TASKKILL",
                    "TASKLIST",
                    "TIME",
                    "TIMEOUT",
                    "TITLE",
                    "TRACERT",
                    "TREE",
                    "TSKILL",
                    "TYPE",
                    "TYPEPERF",
                    "TZUTIL",
                    "VAULTCMD",
                    "VER",
                    "VERIFY",
                    "VOL",
                    "WHERE",
                    "WHOAMI",
                    "XCOPY",
                    "XWIZARD"
                };
                cout << dye::green("[ </> ] ") + dye::aqua("Possible Matches:\n\n");
                for (int i = 0; i < 158; i++) {
                    if (strstr(DOS_DIC[i].c_str(),DOS_CMD.c_str())){
                        cout << dye::aqua(DOS_DIC[i] + "\n");
                    }
                }
                cout << "\n";
            };
            void PathAutoComplete(){
                cout << dye::green("[ </> ] ") + dye::aqua("Possible Matching Files:\n\n");
                system("dir /b > PAC.log");
                CReadFile("PAC.log",1);
                cout << "\n";
            }
            void Generate_CMD_HELP(string Command){
                string Help_filename = Command + ".arghelp";
                if(filesystem::exists(Help_filename) && filesystem::is_regular_file(Help_filename)){
                    CReadFile(Help_filename,2);
                }else{
                    cout << dye::red("[-] ") + dye::light_aqua("Unable to find Help file.\n");
                }
            }
    };
}

#endif
