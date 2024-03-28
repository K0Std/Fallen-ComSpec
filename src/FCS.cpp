#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cstring>
#include <color.hpp>
using namespace std;
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
bool contains(string str1, string str2) {
 // returns true if str1 contains str2, else false
 
 return (str1.find(str2) != string::npos);
}
string ConvertToUppercase(string Input){
    string ToReturn;
    for (int i = 0;i < Input.size();i++){
        ToReturn[i] = Input[i] - 32;
    }
    return ToReturn;
};
string ConvertToLowercase(string Input){
    string ToReturn;
    for (int i = 0;i < Input.size();i++){
        ToReturn[i] = Input[i] + 32;
    }
    return ToReturn;
};
void CReadFile(string filename){
    ifstream file;
    string Content;
    file.open(filename);
    while (getline(file,Content)){
        cout << dye::blue("[*] ") + dye::aqua(Content) + "\n";
    }
    file.close();
    string EndCommand = "del " + filename;
    system(EndCommand.c_str());
}
class Shell{
    public:
        int ERR_CODE;
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
                    CReadFile("NetUtils.log");
                    break;
                }else if (argv[i] == "/Show:AdvancedConfiguration"){
                    system("ipconfig /allcompartments /all > NetUtils.log");
                    CReadFile("NetUtils.log");
                    break;
                }else if (argv[i] == "/Administrative" and argv[i + 1] == "/Configuration:Reset"){
                    system("ipconfig /flushdns > NetUtils.log");
                    CReadFile("NetUtils.log");
                    system("ipconfig /registerdns > NetUtils.log");
                    CReadFile("NetUtils.log");
                    system("ipconfig /release > NetUtils.log");
                    CReadFile("NetUtils.log");
                    system("ipconfig /renew > NetUtils.log");
                    CReadFile("NetUtils.log");
                    system("netsh int ip reset > NetUtils.log");
                    CReadFile("NetUtils.log");
                    system("netsh winsock reset > NetUtils.log");
                    CReadFile("NetUtils.log");
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
                "ESENTUTL",
                "EXIT",
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
            cout << dye::green("[ </> ] ") + dye::aqua("Possible Matches:\n");
            for (int i = 0; i < 158; i++) {
                if (contains(DOS_DIC[i], DOS_CMD)) {
                    cout << dye::aqua(ConvertToLowercase(DOS_DIC[i]) + "\n");
                }
            }
        };
        void PathAutoComplete(string PathToRead){
            cout << dye::green("[ </> ] ") + dye::aqua("Possible Matches:\n");
            string Command = "dir /b " + PathToRead;
            this->Eval(Command);
        }
};
void Start(string Command){
    auto Console = Shell();
    while (true){
        cout << dye::purple("FallenCOMSPEC: ");
        cout << dye::light_aqua(filesystem::current_path().string() + "\n");
        cout << dye::green("$ ");
        getline(cin,Command);
        if (Command == ""){
            continue;
        }
        if (strstr(Command.c_str(),"cd ")){
            string New_Path = Command;
            New_Path.erase(0,3);
            filesystem::current_path(New_Path);
        }else if (strstr(Command.c_str(),"NetUtils") or strstr(Command.c_str(),"netutils")){
            vector<string> NetUtilsARGV;
            split(Command,NetUtilsARGV,' ');
            Console.NetUtils(NetUtilsARGV);
        }else if (strstr(Command.c_str(),"chdir ")){
            string New_Path = Command;
            New_Path.erase(0,6);
            filesystem::current_path(New_Path);
        }else if (strstr(Command.c_str(),"\t")){
            Command.erase(Command.find("\t"));
            Console.AutoComplete(ConvertToUppercase(Command));
        }else if (strstr(Command.c_str(),"^") and strstr(Command.c_str(),".\\")){
            Console.PathAutoComplete(".");
        }else if (Command == "exit"){
            break;
        }else{
            Console.Eval(Command);
        }
    };
    };
int main(int argc,char* argv[]){
    system("title FALLEN COMSPEC");
    Start("");
    return 0;
};
